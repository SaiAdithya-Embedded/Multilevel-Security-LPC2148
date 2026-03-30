#include <LPC21xx.h>
#define LCD_D  (0xFF << 6)   // Data on P0.6–P0.13
#define RS     (1<<4)
#define EN     (1<<5)

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void lcd_str(char *);

void LCD_INIT(void)
{
    IODIR0 |= LCD_D | RS | EN;

    delay_ms(20);

    LCD_CMD(0x38);
    LCD_CMD(0x0C);
    LCD_CMD(0x01);
    LCD_CMD(0x80);
}

void LCD_CMD(unsigned char cmd)
{
    IOCLR0 = LCD_D;          // Clear data pins
    IOSET0 = (cmd << 6);     // Shift command to P0.6–P0.13

    IOCLR0 = RS;             // RS = 0
    IOSET0 = EN;
    delay_ms(2);
    IOCLR0 = EN;
}

void LCD_DATA(unsigned char data)
{
    IOCLR0 = LCD_D;          // Clear data pins
    IOSET0 = (data << 6);    // Shift data to P0.6–P0.13

    IOSET0 = RS;             // RS = 1
    IOSET0 = EN;
    delay_ms(2);
    IOCLR0 = EN;
}

void lcd_str(char *s)
{
    while(*s)
        LCD_DATA(*s++);
}
