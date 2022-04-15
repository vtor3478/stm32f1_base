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
    start();                  //��ʼ�ź�
    Write_Byte(SlaveAddress);   //�����豸��ַ+д�ź�
    Write_Byte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    Write_Byte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ�ڲ��Ĵ���*************************
unsigned char Single_Read_HMC5883(char REG_Address)
{
    unsigned char REG_data;
    start();                          //��ʼ�ź�
    Write_Byte(SlaveAddress);           //�����豸��ַ+д�ź�
    Write_Byte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    start();                          //��ʼ�ź�
    Write_Byte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=Read_Byte(1);              //�����Ĵ�������
 
	stop();                           //ֹͣ�ź�
    return REG_data; 
}
//******************************************************
//
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//
//******************************************************
unsigned char* Multiple_read_HMC5883(void)
{
    char i;
    start();                          //��ʼ�ź�
    Write_Byte(SlaveAddress);           //�����豸��ַ+д�ź�
    Write_Byte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    start();                          //��ʼ�ź�
    Write_Byte(SlaveAddress+1);         //�����豸��ַ+���ź�
    for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��g_hmc5883Data
    {
        // g_hmc5883Data[0]�洢����
        if (i == 5)
        {
            g_hmc5883Data[i] = Read_Byte(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
            g_hmc5883Data[i] = Read_Byte(0);                //��ӦACK
        }
    }
    stop();                          //ֹͣ�ź�
    Delay5ms();
    return g_hmc5883Data;
}

//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****
void Init_HMC5883()
{
    iic_remap(hmc5883_scl_write,hmc5883_sda_write,hmc5883_sda_read);
    Single_Write_HMC5883(0x02,0x00);  //
}
