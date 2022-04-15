#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	
#include "iic/soft_iic_if.h"


void(oled_iic_scl_write)(unsigned char val);
void(oled_iic_sda_write)(unsigned char val);
unsigned char(oled_iic_sda_read)(void);
//-----------------测试LED端口定义---------------- 

#define SCL_PORT		GPIOA
#define SCL_PIN			GPIO_Pin_5
#define SDA_PORT		GPIOA
#define SDA_PIN			GPIO_Pin_7


#define OLED_SCL_Clr() GPIO_ResetBits(SCL_PORT,SCL_PIN)//SCL
#define OLED_SCL_Set() GPIO_SetBits(SCL_PORT,SCL_PIN)

#define OLED_SDA_Clr() GPIO_ResetBits(SDA_PORT,SDA_PIN)//SDA
#define OLED_SDA_Set() GPIO_SetBits(SDA_PORT,SDA_PIN)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

void OLED_I2C_Init(IIC_IF *IIC_If);

#endif

