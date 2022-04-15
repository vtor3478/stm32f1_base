#ifndef _IIC_IF_H_
#define _IIC_IF_H_
#include "delay/delay.h"


typedef struct{
	void (*Start)(void);
	void (*Stop)(void);
	void (*WriteByte)(unsigned char);
	unsigned char (*ReadByte)(void);
	void (*SendAck)(void);
	void (*SendNAck)(void);
	unsigned char (*WaitAck)(void);
}IIC_IF;

extern IIC_IF softIicIf ;
extern unsigned short iic_error;

void iic_remap(void(*device_scl_write)(unsigned char),
                void(*device_sda_write)(unsigned char),
                unsigned char(*device_sda_read)(void));

void start();
void write_byte(unsigned char dat);
unsigned char wait_ack();
unsigned char read_byte();
void ack(void);
void nak();
void stop();

#endif
								