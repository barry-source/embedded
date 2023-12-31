#include "iic_paj7620.h"
#include "stdio.h"
#include "iic.h"
#include "motor.h"

#define INIT_REG_ARRAY_SIZE (sizeof(initRegisterArray)/sizeof(initRegisterArray[0]))

uint16_t status = 0;

uint8_t initRegisterArray[][2] = {	// Initial Gesture
  {0xEF,0x00},
	{0x32,0x29},
	{0x33,0x01},
	{0x34,0x00},
	{0x35,0x01},
	{0x36,0x00},
	{0x37,0x07},
	{0x38,0x17},
	{0x39,0x06},
	{0x3A,0x12},
	{0x3F,0x00},
	{0x40,0x02},
	{0x41,0xFF},
	{0x42,0x01},
	{0x46,0x2D},
	{0x47,0x0F},
	{0x48,0x3C},
	{0x49,0x00},
	{0x4A,0x1E},
	{0x4B,0x00},
	{0x4C,0x20},
	{0x4D,0x00},
	{0x4E,0x1A},
	{0x4F,0x14},
	{0x50,0x00},
	{0x51,0x10},
	{0x52,0x00},
	{0x5C,0x02},
	{0x5D,0x00},
	{0x5E,0x10},
	{0x5F,0x3F},
	{0x60,0x27},
	{0x61,0x28},
	{0x62,0x00},
	{0x63,0x03},
	{0x64,0xF7},
	{0x65,0x03},
	{0x66,0xD9},
	{0x67,0x03},
	{0x68,0x01},
	{0x69,0xC8},
	{0x6A,0x40},
	{0x6D,0x04},
	{0x6E,0x00},
	{0x6F,0x00},
	{0x70,0x80},
	{0x71,0x00},
	{0x72,0x00},
	{0x73,0x00},
	{0x74,0xF0},
	{0x75,0x00},
	{0x80,0x42},
	{0x81,0x44},
	{0x82,0x04},
	{0x83,0x20},
	{0x84,0x20},
	{0x85,0x00},
	{0x86,0x10},
	{0x87,0x00},
	{0x88,0x05},
	{0x89,0x18},
	{0x8A,0x10},
	{0x8B,0x01},
	{0x8C,0x37},
	{0x8D,0x00},
	{0x8E,0xF0},
	{0x8F,0x81},
	{0x90,0x06},
	{0x91,0x06},
	{0x92,0x1E},
	{0x93,0x0D},
	{0x94,0x0A},
	{0x95,0x0A},
	{0x96,0x0C},
	{0x97,0x05},
	{0x98,0x0A},
	{0x99,0x41},
	{0x9A,0x14},
	{0x9B,0x0A},
	{0x9C,0x3F},
	{0x9D,0x33},
	{0x9E,0xAE},
	{0x9F,0xF9},
	{0xA0,0x48},
	{0xA1,0x13},
	{0xA2,0x10},
	{0xA3,0x08},
	{0xA4,0x30},
	{0xA5,0x19},
	{0xA6,0x10},
	{0xA7,0x08},
	{0xA8,0x24},
	{0xA9,0x04},
	{0xAA,0x1E},
	{0xAB,0x1E},
	{0xCC,0x19},
	{0xCD,0x0B},
	{0xCE,0x13},
	{0xCF,0x64},
	{0xD0,0x21},
	{0xD1,0x0F},
	{0xD2,0x88},
	{0xE0,0x01},
	{0xE1,0x04},
	{0xE2,0x41},
	{0xE3,0xD6},
	{0xE4,0x00},
	{0xE5,0x0C},
	{0xE6,0x0A},
	{0xE7,0x00},
	{0xE8,0x00},
	{0xE9,0x00},
	{0xEE,0x07},
	{0xEF,0x01},
	{0x00,0x1E},
	{0x01,0x1E},
	{0x02,0x0F},
	{0x03,0x10},
	{0x04,0x02},
	{0x05,0x00},
	{0x06,0xB0},
	{0x07,0x04},
	{0x08,0x0D},
	{0x09,0x0E},
	{0x0A,0x9C},
	{0x0B,0x04},
	{0x0C,0x05},
	{0x0D,0x0F},
	{0x0E,0x02},
	{0x0F,0x12},
	{0x10,0x02},
	{0x11,0x02},
	{0x12,0x00},
	{0x13,0x01},
	{0x14,0x05},
	{0x15,0x07},
	{0x16,0x05},
	{0x17,0x07},
	{0x18,0x01},
	{0x19,0x04},
	{0x1A,0x05},
	{0x1B,0x0C},
	{0x1C,0x2A},
	{0x1D,0x01},
	{0x1E,0x00},
	{0x21,0x00},
	{0x22,0x00},
	{0x23,0x00},
	{0x25,0x01},
	{0x26,0x00},
	{0x27,0x39},
	{0x28,0x7F},
	{0x29,0x08},
	{0x30,0x03},
	{0x31,0x00},
	{0x32,0x1A},
	{0x33,0x1A},
	{0x34,0x07},
	{0x35,0x07},
	{0x36,0x01},
	{0x37,0xFF},
	{0x38,0x36},
	{0x39,0x07},
	{0x3A,0x00},
	{0x3E,0xFF},
	{0x3F,0x00},
	{0x40,0x77},
	{0x41,0x40},
	{0x42,0x00},
	{0x43,0x30},
	{0x44,0xA0},
	{0x45,0x5C},
	{0x46,0x00},
	{0x47,0x00},
	{0x48,0x58},
	{0x4A,0x1E},
	{0x4B,0x1E},
	{0x4C,0x00},
	{0x4D,0x00},
	{0x4E,0xA0},
	{0x4F,0x80},
	{0x50,0x00},
	{0x51,0x00},
	{0x52,0x00},
	{0x53,0x00},
	{0x54,0x00},
	{0x57,0x80},
	{0x59,0x10},
	{0x5A,0x08},
	{0x5B,0x94},
	{0x5C,0xE8},
	{0x5D,0x08},
	{0x5E,0x3D},
	{0x5F,0x99},
	{0x60,0x45},
	{0x61,0x40},
	{0x63,0x2D},
	{0x64,0x02},
	{0x65,0x96},
	{0x66,0x00},
	{0x67,0x97},
	{0x68,0x01},
	{0x69,0xCD},
	{0x6A,0x01},
	{0x6B,0xB0},
	{0x6C,0x04},
	{0x6D,0x2C},
	{0x6E,0x01},
	{0x6F,0x32},
	{0x71,0x00},
	{0x72,0x01},
	{0x73,0x35},
	{0x74,0x00},
	{0x75,0x33},
	{0x76,0x31},
	{0x77,0x01},
	{0x7C,0x84},
	{0x7D,0x03},
	{0x7E,0x01},
};

void paj7620_init(void) {
	paj_iic_init();
	paj_it_init();
	uint8_t r = paj_init();
	printf("===%d\r\n", r);
}

void paj_iic_init() {	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = IIC_SCL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = IIC_SDA_PIN;
	HAL_GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStruct);
	
	// 拉高SCL SDA 使总线空闲
	HAL_GPIO_WritePin(IIC_GPIO_PORT, IIC_SCL_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IIC_GPIO_PORT, IIC_SDA_PIN, GPIO_PIN_SET);
}

void paj_it_init(void) {
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef gpioInit;
	gpioInit.Pin = PAJ7620_IT_PIN;
	gpioInit.Mode = GPIO_MODE_IT_FALLING;
	HAL_GPIO_Init(PAJ7620_IT_PORT, &gpioInit);
}

uint8_t paj7620_getInterrupt(void) {
	return HAL_GPIO_ReadPin(PAJ7620_IT_PORT, PAJ7620_IT_PIN) == 0;
}

uint8_t paj_init(void) {
	uint8_t data = 0, rtn = 0;
	uint16_t cnt = 0;
	
	iic_delay_us(700);	//Wait 700us for PAJ7620U2 to stabilize
	rtn = paj7620_sekect_bank(PAJ7620_BANK0);
	//printf("rtn:===%d\r\n", rtn);
	// 读0x00地址，正常会返回0x20
	rtn = iic_read_7620(PAJ7620_ADDRESS, PAJ7620_ADDR_PART_ID_0, &data, 1);
	if(rtn) {
		return rtn;
	}
	if(data != PAJ7620_PART_ID_0)
	{
		return 0xff;
	}
	// 这一步文档上没有找到说明
	rtn = iic_read_7620(PAJ7620_ADDRESS, PAJ7620_ADDR_PART_ID_1, &data, 1);
	if(rtn)
	{
		return rtn;
	}
	if(data != PAJ7620_PART_ID_1)
	{
		return 0xfe;
	}
	for (cnt = 0; cnt < INIT_REG_ARRAY_SIZE; cnt++) 
	{
		rtn = iic_write_7620(PAJ7620_ADDRESS, initRegisterArray[cnt][0], &initRegisterArray[cnt][1], 1);
		if(rtn)
		{
			return rtn;
		}
	}
	
	paj7620_sekect_bank(PAJ7620_BANK1);  //gesture flage reg in Bank1
	// 这一步文档上没有找到说明
	//data = 0xB7;	// far mode 120 fps
	//data = 0x12;  		// near mode 240 fps
	//iic_write_7620(PAJ7620_ADDRESS, 0x65, &data, 1); 

	paj7620_sekect_bank(PAJ7620_BANK0);  //gesture flage reg in Bank0
	
	return 0;
}

uint8_t paj7620_sekect_bank(uint8_t bank) {
	uint8_t rtn = 0;
	if(bank == PAJ7620_BANK0 || bank == PAJ7620_BANK1)
	{
		rtn = iic_write_7620(PAJ7620_ADDRESS, PAJ7620_REGITER_BANK_SEL, &bank, 1);
		iic_delay_us(300);
		//printf("rtn1:===%d\r\n", rtn);
	}
	else
	{
		rtn = 0xff;
	}
	return rtn;
}

uint16_t paj7620_get_gesture(void) {
	uint8_t rRtn = 0, rData[2] = {0};
	uint16_t gCode = 0;
	rRtn  = iic_read_7620(PAJ7620_ADDRESS, PAJ7620_ADDR_GES_PS_DET_FLAG_0, rData, 2);
	if(rRtn)
	{
		return rRtn;
	}
	gCode = (rData[1]<<8) & 0xff00 | rData[0];
	return gCode;
}

void paj7620_action(void) {
	 switch (status) {
		case 0x01: // up
			paj7620_up();
			break;
		case 0x02: // down
			paj7620_down();
			break;
		case 0x04: // left
			paj7620_left();
			break;
		case 0x08: // right
			paj7620_right();
			break;
		case 0x10: // push
			paj7620_push();
			break;
		case 0x20: // pop
			paj7620_pop();
			break;
		case 0x40: // rotate right
			paj7620_rotate_right();
			break;
		case 0x80: // rotate left
			paj7620_rotate_left();
			break;
		case 0x100:// wave
			paj7620_wave();
			break;
		case 0x00: // nothing
			paj7620_nothing();
		 	break;
		default:
			paj7620_error();
	}
}

void paj7620_up(void) {
	printf("up\r\n");
	forward();
	status = 0;
	HAL_Delay(500);
	stop();
}

void paj7620_down(void) {
	printf("down\r\n");
	backward();
	status = 0;
	HAL_Delay(500);
	stop();
}
void paj7620_left(void) {
	printf("left\r\n");
	rightward();
	status = 0;
	HAL_Delay(500);
	stop();
}

void paj7620_right(void) {
	printf("right\r\n");
	leftward();
	status = 0;
	HAL_Delay(500);
	stop();
}

void paj7620_push(void) {
	printf("push\r\n");
	backward();
	status = 0;
	HAL_Delay(500);
	stop();
}

void paj7620_pop(void)
{
	printf("pop\r\n");
}

void paj7620_rotate_right(void) {
	printf("rotate right\r\n");
}

void paj7620_rotate_left(void) {
	printf("rotate left\r\n");
}

void paj7620_wave(void) {
	printf("wave\r\n");
}

void paj7620_nothing(void) {
	printf("nothing\r\n");
}

void paj7620_error(void) {
	printf("error\r\n");
}




