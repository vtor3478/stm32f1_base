#ifndef __HMC5883_H_
#define __HMC5883_H_

#include "iic/soft_iic_if.h"


//定义器件在IIC总线中的从地址
#define	SlaveAddress   0x3C



void Init_HMC5883(void);
unsigned char Single_Read_HMC5883(uchar REG_Address);
unsigned char* Multiple_read_HMC5883();
#endif
