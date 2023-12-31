#include "car_function.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "usart.h"
#include "su03.h"
#include "sensor.h"
#include "motor.h"
#include "sg90.h"
#include "sr04.h"
#include "tim.h"
#include "iic_paj7620.h"
#include "dht11.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

// 小车头部3.5cm
#define FRONT_DIS 3.5
// 小车头部7cm
#define LEFT_DIS 7

double disLeft = 0;
double disMiddle = 0;
double disRight = 0;
char dir = MIDDLE;

enum Mode lastMode = stopMode;

// 温湿度不能频繁刷新，影响小车的运行，计次刷新一次
uint32_t count = 0;

//速度
unsigned int speedCnt;
char speedString[24];

// 保存速度任务Handle
osTimerId SpeedHandle;

void follow() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		speedCnt = 0;
		osTimerStart(SpeedHandle, 1000);
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : follow");
		HAL_Delay(100);
	}

	if(leftFollowValue() == GPIO_PIN_RESET && rightFollowValue() == GPIO_PIN_RESET) {
		forward();
	}
	if(leftFollowValue() == GPIO_PIN_RESET && rightFollowValue() == GPIO_PIN_SET) {
		leftward();
	}
	if(leftFollowValue() == GPIO_PIN_SET && rightFollowValue() == GPIO_PIN_RESET) {
		rightward();
	}
	if(leftFollowValue() == GPIO_PIN_SET && rightFollowValue() == GPIO_PIN_SET) {
		stop();
	}
}

void avoid() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		speedCnt = 0;
		osTimerStart(SpeedHandle, 1000);
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : avoid");
		HAL_Delay(500);
	}

	if(dir != MIDDLE) {
		dir = MIDDLE;
		turn_90_degree();
		HAL_Delay(300);
	}
	distance = 0;
	trig();
	while(!distance);
	disMiddle = distance - FRONT_DIS;
	printf("front:%f\r\n", distance);
	if(disMiddle > 35) {
		forward();
	} else if(disMiddle < 10) {
		backward();
	} else {
		stop();
		turn_180_degree();
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disLeft = distance - FRONT_DIS;
		printf("left:%f\r\n", distance);
		
		turn_90_degree();
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disMiddle = distance - LEFT_DIS;
		if(disMiddle < 10) 
			backward();
		turn_0_degree();
		dir = RIGHT;
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disRight = distance - LEFT_DIS;
		printf("right:%f\r\n", distance);
		if(disLeft < disRight) {
			rightward();
			HAL_Delay(150);
			stop();
		} 
		if(disLeft > disRight){
			leftward();
			HAL_Delay(150);
			stop();
		}
	}
}

void traceing() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(PWM);
		HAL_Delay(500);
		speedCnt = 0;
		osTimerStart(SpeedHandle, 1000);
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : trace");
	}

	if(leftTraceValue() == GPIO_PIN_RESET && rightTraceValue() == GPIO_PIN_RESET) {
		forward();
	}
	if(leftTraceValue() == GPIO_PIN_RESET && rightTraceValue() == GPIO_PIN_SET) {
		leftward();
	}
	if(leftTraceValue() == GPIO_PIN_SET && rightTraceValue() == GPIO_PIN_RESET) {
		rightward();
	}
	if(leftTraceValue() == GPIO_PIN_SET && rightTraceValue() == GPIO_PIN_SET) {
		stop();
	}
}

void stop_car() {
	if(runMode != lastMode) {
		lastMode = runMode;
		speedCnt = 0;
		osTimerStop(SpeedHandle);
		speedCnt = 0;
		oled_clear_1_line();
		oled_show_string(1,2, "mode : stop");
		// 主要是复原舵机正前方
		reset();
	}
	display_temp_humi();
}

void gesture() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		speedCnt = 0;
		osTimerStart(SpeedHandle, 1000);
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : gesture");
		HAL_Delay(500);
	}
	paj7620_action();
}

void test() { 
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : test");
		HAL_Delay(500);
	}
}
	
void display_temp_humi() {
	if(runMode != stopMode) {
		return;
	} 
	count = 0;
	//记得关中断，否则会影响DHT11采集数据
	//HAL_TIM_Base_Stop_IT(&htim3);
	char msg[16];
	
	uint8_t result = trig_dht();
	//printf("result: %d\r\n", result);
	receive_data();
	
	oled_clear(4, 8, 56, 128);
	sprintf(msg, "Temp : %d.%d C", datas[2], datas[3]);
	oled_show_string(3,2,msg);
	sprintf(msg, "Humi : %d.%d %%", datas[0], datas[1]);
	oled_show_string(4,2,msg);;
	HAL_Delay(500);
}

void initTask(osTimerId SpeedTimerHandle) {
	SpeedHandle = SpeedTimerHandle;
}

void init() {
	//开启串口中断蓝牙在用
	HAL_UART_Receive_IT(&huart1, &buf, 1);
	
	//开启pwm，并旋转至最前方
	sg90_init();
	HAL_Delay(100);
	paj7620_init();
	HAL_Delay(100);
	//初始化oled
	oled_init();
	oled_clear_all();
	oled_show_string(1,2,"mode : stop");
	oled_show_string(2,2, "speed: ----");
	oled_show_string(3,2, "Temp :--.--");
	oled_show_string(4,2, "Humi :--.--");
	
	
}

void reset() {
	if(runMode == followMode || runMode == tracingMode || runMode == avoidMode || runMode == gestureMode) {
		//HAL_TIM_Base_Start_IT(&htim3);
	} else {
		//HAL_TIM_Base_Stop_IT(&htim3);
	}
	if(runMode != tracingMode) {
		//切换到其它模式，将舵机指向正前方
		turn_90_degree();
	}
	//停止小车
	stop();
}

//////////////////////////中断/////////////////////////////

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	//脉冲测速
	if(GPIO_Pin == GPIO_PIN_10) {
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET)
			speedCnt++;
	}
	//超声波echo
	if(GPIO_Pin == GPIO_PIN_12) {
		//while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET);
		HAL_TIM_Base_Start(&htim1);
		__HAL_TIM_SetCounter(&htim1, 0);
		
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_SET);
		HAL_TIM_Base_Stop(&htim1);
		
		int cnt = __HAL_TIM_GetCounter(&htim1);
		distance = 340 * 0.000001 * cnt * 100 / 2;
	}
	//手势中断
	if(GPIO_Pin == GPIO_PIN_7) {
		uint16_t gCode = 0;
		gCode = paj7620_get_gesture();
		status = gCode;
		printf("%d====》", gCode);
	}
}
