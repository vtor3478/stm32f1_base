#include "iic/soft_iic_if.h"
#include "hmc5883/hmc5883.h"

unsigned char g_hmc5883Data[8];

static void hmc5883_scl_write(char status)
{
    hmc5883_SCL = status;
}

static void hmc5883_sda_write(char status)
{
    hmc5883_SDA = status;
}

static char hmc5883_sda_read(void)
{
    return hmc5883_SDA;
}



void Single_Write_HMC5883(char REG_Address,char REG_data)
{
    start();                  //起始信号
    Write_Byte(SlaveAddress);   //发送设备地址+写信号
    Write_Byte(REG_Address);    //内部寄存器地址，请参考中文pdf 
    Write_Byte(REG_data);       //内部寄存器数据，请参考中文pdf
    stop();                   //发送停止信号
}

//********单字节读取内部寄存器*************************
unsigned char Single_Read_HMC5883(char REG_Address)
{
    unsigned char REG_data;
    start();                          //起始信号
    Write_Byte(SlaveAddress);           //发送设备地址+写信号
    Write_Byte(REG_Address);                   //发送存储单元地址，从0开始	
    start();                          //起始信号
    Write_Byte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=Read_Byte(1);              //读出寄存器数据
 
	stop();                           //停止信号
    return REG_data; 
}
//******************************************************
//
//连续读出HMC5883内部角度数据，地址范围0x3~0x5
//
//******************************************************
unsigned char* Multiple_read_HMC5883(void)
{
    char i;
    start();                          //起始信号
    Write_Byte(SlaveAddress);           //发送设备地址+写信号
    Write_Byte(0x03);                   //发送存储单元地址，从0x3开始	
    start();                          //起始信号
    Write_Byte(SlaveAddress+1);         //发送设备地址+读信号
    for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中g_hmc5883Data
    {
        // g_hmc5883Data[0]存储数据
        if (i == 5)
        {
            g_hmc5883Data[i] = Read_Byte(1);                //最后一个数据需要回NOACK
        }
        else
        {
            g_hmc5883Data[i] = Read_Byte(0);                //回应ACK
        }
    }
    stop();                          //停止信号
    Delay5ms();
    return g_hmc5883Data;
}

//初始化HMC5883，根据需要请参考pdf进行修改****
void Init_HMC5883()
{
    iic_remap(hmc5883_scl_write,hmc5883_sda_write,hmc5883_sda_read);
    Single_Write_HMC5883(0x02,0x00);  //
}
