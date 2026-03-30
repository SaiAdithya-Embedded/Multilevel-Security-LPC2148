#include<lpc21xx.h>
#define c0 (IOPIN1 &(1<<20))
#define c1 (IOPIN1 &(1<<21))
#define c2 (IOPIN1 &(1<<22))
#define c3 (IOPIN1 &(1<<23))

#define r0 1<<16
#define r1 1<<17
#define r2 1<<18
#define r3 1<<19
unsigned int key_lut[4][4]={{7,8,9,0},{4,5,6,0},{1,2,3,0},{13,0,15,16}};

unsigned int keyscan(void)
{
	unsigned char row_val,col_val;
	IODIR1|=r0|r1|r2|r3;//set direction of rows as Output
	
	while(1) //inner while start
	{
		IOCLR1=r0|r1|r2|r3;
		IOSET1=c0|c1|c2|c3;
		while((c0&&c1&&c2&&c3)==1);//waiting for key press
		
		//testing for row0
		
		IOCLR1=r0;
		IOSET1=r1|r2|r3;
		
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=0;
			break;
			
		}
		
		//testing for row1
		
		IOCLR1=r1;
		IOSET1=r0|r2|r3;
		
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=1;
			break;
			
		}
		
		//testing for row2
		
		IOCLR1=r2;
		IOSET1=r0|r1|r3;
		
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=2;
			break;
			
		}
		//testing for row3
		
		IOCLR1=r3;
		IOSET1=r0|r1|r2;
		
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=3;
			break;
			
		}
		
	}//while
	
	if(c0==0)
		col_val=0;
	else if(c1==0)
		col_val=1;
	else if(c2==0)
		col_val=2;
	else 
		col_val=3;
	delay_ms(150);//to de-bouncing the switch
	while((c0&&c1&&c2&&c3)==0);//waiting for key release
	return key_lut[row_val][col_val];
}

