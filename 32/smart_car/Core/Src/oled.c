#include "oled.h"
#include "oledFont.h"
#include "i2c.h"

unsigned char peiqi[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,0x90,0x50,0x50,0x90,0x20,0x7E,
0xC1,0x1D,0x64,0x44,0x79,0x02,0xBC,0x90,0xD0,0x50,0x90,0x88,0x28,0x68,0xA8,0x28,
0xA8,0x04,0xE4,0x54,0x54,0x64,0x68,0x48,0x90,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x04,0xC9,0x32,0x84,0x65,0x13,0x08,
0x05,0x3C,0x46,0x92,0x81,0x05,0xB9,0x83,0x6C,0x10,0x10,0x14,0x17,0x20,0x0C,0x03,
0x07,0x08,0x13,0xA4,0xAC,0x4A,0x12,0x92,0x4F,0x20,0x0F,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x07,0xF0,0xFE,0x04,0x72,0x88,0x09,
0x0A,0x8A,0x64,0x08,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x04,
0xCA,0x71,0x85,0x3C,0xC2,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1C,0x61,0x8E,0x13,0x44,0x84,0x85,
0x05,0x04,0x02,0x01,0x03,0x04,0x09,0x1A,0x12,0x14,0x14,0x14,0x12,0x8B,0x48,0x82,
0xB1,0x4C,0xE3,0x1C,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xF0,0x08,0x08,0x48,0x08,0xA8,0x84,0x54,0xC4,0x62,0x02,0xE3,0x1C,0x06,0x02,0x04,
0x05,0x09,0x0A,0x0A,0x0A,0x02,0x0A,0x0A,0x1A,0x19,0x01,0x05,0x04,0x02,0x02,0x01,
0x03,0x0C,0x71,0x82,0x22,0xC4,0x54,0x44,0xA8,0x08,0x68,0x08,0x08,0x40,0x10,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x31,0x4A,0x8A,0x06,0x12,0x83,0xA2,0x84,0x07,0xE0,0x0F,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xF8,0x03,0x3C,0xE0,0x00,0x00,0x02,0x01,0x02,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x00,0x0C,0x03,0x10,0x17,0x14,0x14,0x14,0xD4,0x34,0x84,
0x04,0xF4,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xF4,0x04,0xC4,0x04,
0xF4,0x94,0x54,0x54,0x54,0x57,0x10,0x4F,0xA0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x01,0x08,0x08,
0x10,0x15,0x15,0x15,0x15,0x11,0x0C,0x00,0x00,0x00,0x00,0x00,0x07,0x08,0x00,0x08,
0x0A,0x0A,0x0A,0x0A,0x08,0x00,0x01,0x90,0x90,0x00,0x80,0x80,0x90,0x90,0x80,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void iic_write_cmd(uint8_t cmd) {
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT,
										&cmd, 1, 0xff);
}

void iic_write_data(uint8_t data) {
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT,
										&data, 1, 0xff);
}

void oled_init() {
	iic_write_cmd(0xAE);//--display off
	iic_write_cmd(0x00);//---set low column address
	iic_write_cmd(0x10);//---set high column address
	iic_write_cmd(0x40);//--set start line address  
	iic_write_cmd(0xB0);//--set page address
	iic_write_cmd(0x81); // contract control
	iic_write_cmd(0xFF);//--128   
	iic_write_cmd(0xA1);//set segment remap 
	iic_write_cmd(0xA6);//--normal / reverse
	iic_write_cmd(0xA8);//--set multiplex ratio(1 to 64)
	iic_write_cmd(0x3F);//--1/32 duty
	iic_write_cmd(0xC8);//Com scan direction
	iic_write_cmd(0xD3);//-set display offset
	iic_write_cmd(0x00);//
	
	iic_write_cmd(0xD5);//set osc division
	iic_write_cmd(0x80);//
	
	iic_write_cmd(0xD8);//set area color mode off
	iic_write_cmd(0x05);//
	
	iic_write_cmd(0xD9);//Set Pre-Charge Period
	iic_write_cmd(0xF1);//
	
	iic_write_cmd(0xDA);//set com pin configuartion
	iic_write_cmd(0x12);//
	
	iic_write_cmd(0xDB);//set Vcomh
	iic_write_cmd(0x30);//
	
	iic_write_cmd(0x8D);//set charge pump enable
	iic_write_cmd(0x14);//
	
	iic_write_cmd(0xAF);//--turn on oled panel		
}


void oled_clear() {
	int i, j;
	iic_write_cmd(0x20);
	iic_write_cmd(0x02);
	for(i = 0; i < 8; i ++) {
		iic_write_cmd(0xB0+i);
		iic_write_cmd(0x00);
		iic_write_cmd(0x10);
		for(j = 0; j < 128; j ++) {
			iic_write_data(0);
		}
	}
}

void oled_image(unsigned char *image)
{
	unsigned char i; 
	unsigned int j;
	
	for(i=0;i<8;i++){
		iic_write_cmd(0xB0 + i);
		iic_write_cmd(0x00);
		iic_write_cmd(0x10);
	
		for(j = 128 * i; j<(128 * (i+1));j++){
			iic_write_data(image[j]);
		}
	}
}


void Oled_Show_Char(char row,char col,char oledChar) { //row*2-2
	unsigned int  i;
	iic_write_cmd(0xb0+(row*2-2));                           //page 0
	iic_write_cmd(0x00+(col&0x0f));                          //low
	iic_write_cmd(0x10+(col>>4));                            //high	
	for(i=((oledChar-32)*16);i<((oledChar-32)*16+8);i++){
		iic_write_data(F8X16[i]);                            //写数据oledTable1
	}

	iic_write_cmd(0xb0+(row*2-1));                           //page 1
	iic_write_cmd(0x00+(col&0x0f));                          //low
	iic_write_cmd(0x10+(col>>4));                            //high
	for(i=((oledChar-32)*16+8);i<((oledChar-32)*16+8+8);i++){
		iic_write_data(F8X16[i]);                            //写数据oledTable1
	}		
}


/******************************************************************************/
// 函数名称：Oled_Show_Char 
// 输入参数：oledChar 
// 输出参数：无 
// 函数功能：OLED显示单个字符
/******************************************************************************/
void oled_show_string(char row,char col,char *str) {
	while(*str!=0){
		Oled_Show_Char(row,col,*str);
		str++;
		col += 8;	
	}		
}


