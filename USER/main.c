//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : OLED I2C接口演示例程(STM32F103系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA5（SCL）
//              D1   PA7（SDA）
//              RES  PD2（SPI模块改成IIC模块需要接此引脚，IIC模块用户请忽略）
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"
#include "iic/soft_iic_if.h"
#include "../usmart/usmart.h"
#include "../usmart/usmart_io.h"

int main(void)
{
	u8 t=' ';
	delay_init();
	uart_init(115200);
	iic_remap(
		oled_iic_scl_write,
		oled_iic_sda_write,
		oled_iic_sda_read);
	OLED_I2C_Init(&softIicIf);
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	memset(USART_RX_BUF,"list\r\n ",7);
	usmart_printf("usmart,show%d",8);
	OLED_Printf(0,8,"oled,show,0,8,%d",8);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			printf(USART_RX_BUF);
			usmart_scan(USART_RX_BUF);
			
			USART_RX_STA = 0;
		}
		//OLED_ShowPicture(0,0,128,64,BMP1,1);
		//OLED_Refresh();
		delay_ms(500);
		//OLED_Clear();
		//OLED_ShowString(20,32,"2014/05/01",16,1);
		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		//OLED_ShowNum(103,48,t,3,16,1);
		OLED_Refresh();
		//OLED_ScrollDisplay(20,4,1);
	}
}

