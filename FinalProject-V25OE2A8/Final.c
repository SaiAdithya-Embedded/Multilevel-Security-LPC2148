#include <LPC21xx.h>
#include <stdlib.h>
#include "type.h"
#include "i2c.h"
#include "i2c.c"
#include "i2c_eeprom.h"
#include "i2c_eeprom.c"
#include "keypad.h"
#include "lcd.h"
#include "delay.h"
#include "UART header.h"

#define I2C_EEPROM_SA 0x50

#define LED   (1<<14)
#define M1    (1<<15)
#define M2    (1<<16)

u8 pass[5];
char input_pass[5];
char otp[5];
char input_otp[5];

void get_password()
{
	int i;
	for(i=0;i<4;i++)
	{
		input_pass[i] = keyscan() + '0';
		LCD_DATA('*');
	}
	input_pass[4] = '\0';
}

int check_password()
{
	int i;

	for(i=0;i<4;i++)
	{
		if(input_pass[i] != pass[i])
			return 0;
	}

	return 1;
}

void generate_otp()
{
	int i;

	for(i=0;i<4;i++)
	{
		otp[i] = (rand() % 10) + '0';
	}

	otp[4] = '\0';
}

void get_otp()
{
	int i;
	for(i=0;i<4;i++)
	{
		input_otp[i] = keyscan() + '0';
		LCD_DATA('*');
	}
	input_otp[4] = '\0';
}

int check_otp()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(input_otp[i] != otp[i])
			return 0;
	}
	return 1;
}

int main()
{
	int attempts = 0;
	IODIR0 = LED | M1 | M2;
	IOSET0=LED;
	IOCLR0 = M1 | M2; 	
	init_i2c();
	LCD_INIT();
  i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,"1234",4);
	i2c_eeprom_seq_read(I2C_EEPROM_SA,0x00,pass,4);

	delay_ms(100);

	LCD_CMD(0x80);
	lcd_str("MULTILEVEL");
	LCD_CMD(0xC0);
	lcd_str("SECURITY");

	delay_ms(1000);

	while(attempts < 3)
	{
		LCD_CMD(0x01);
		LCD_CMD(0x80);
		lcd_str("ENTER PASS");

		LCD_CMD(0xC0);
		get_password();

		if(check_password())
		{
			LCD_CMD(0x01);
			lcd_str("PASS OK");

			UART0_CONFIG();
			rand();
      rand();
      rand();
      generate_otp();   

     UART0_STRING("OTP: ");
     UART0_STRING(otp);
     UART0_STRING("\r\n");

			delay_ms(1000);

			LCD_CMD(0x01);
			lcd_str("ENTER OTP");

			LCD_CMD(0xC0);
			get_otp();

			if(check_otp())
			{
				LCD_CMD(0x01);
				lcd_str("ACCESS OK");

				IOCLR0 = LED;
				IOSET0 = M1;

				while(1);
			}
			else
			{
				LCD_CMD(0x01);
				lcd_str("OTP WRONG");
				delay_ms(1000);
			}
		}
		else
		{
			attempts++;

			LCD_CMD(0x01);
			lcd_str("WRONG PASS");
			delay_ms(1000);
		}
	}
	UART0_CONFIG();
	UART0_STRING("ALERT: WRONG PASSWORD 3 TIMES\r\n");

	LCD_CMD(0x01);
	lcd_str("SYSTEM LOCK");

	while(1);
}