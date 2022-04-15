#include "delay.h"

void Delay500ms()		//@11.0592MHz
{
	volatile unsigned char i, j, k;
	__nop();
	__nop();
	__nop();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay8us()		//@11.0592MHz
{
	volatile unsigned char i;

	__nop();
	__nop();
	i = 19;
	while (--i);
}

void Delay5us()		//@11.0592MHz
{
	volatile unsigned char i;

	__nop();
	i = 11;
	while (--i);
}

void Delay2us()		//@11.0592MHz
{
	volatile unsigned char i;

	i = 3;
	while (--i);
}
