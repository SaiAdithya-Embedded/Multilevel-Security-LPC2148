#include<LPC21xx.h>
void delay_ms(unsigned int sec)
{
	T0PR=15000-1; 
	T0TCR=0X01;
	while(T0TC<sec);
	T0TCR=0X03;
	T0TCR=0X00;   
	}
