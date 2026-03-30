/*Write an ECP to receive and re-transmit characters serially through UART0
of LPC2129*/
#include<LPC21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_STRING(unsigned char *);
unsigned char UART0_RX(void);
void UART0_CONFIG(void)
{
	PINSEL0 |= 0x00000005;//P0.0 as TXD0 and P0.1 as RXD0
	U0LCR=0x83;//Select 8N1 Frame and DLAB is set
	U0FCR = 0x07;  
	U0DLL=97;//To set baud rate
	U0LCR=0x03;//DLAB is cleared to access U0THR & U0RBR
	
}

void UART0_TX(unsigned char d)
{
	while((U0LSR&(1<<5))==0);
	U0THR=d;
	
}

void UART0_STRING(unsigned char *s)
{
	while(*s)
	{
		UART0_TX(*s++);
	}
	
}

unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
	
}
