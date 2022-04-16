//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA5��SCL��
//              D1   PA7��SDA��
//              RES  PD2��SPIģ��ĳ�IICģ����Ҫ�Ӵ����ţ�IICģ���û�����ԣ�
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
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
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
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
		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		//OLED_ShowNum(103,48,t,3,16,1);
		OLED_Refresh();
		//OLED_ScrollDisplay(20,4,1);
	}
}

