#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wr=P3^6;
sbit rd=P3^7;
void init();
void start();
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--); 
}
void main()
{
	init();
	while(1)
	{
		start();
		delay(10);
		rd=0;
		delay(10);
		rd=1;
		delay(10);
		
	}
}
void init()
{
	P0=0;	
}
void start()
{
	wr=1;
	wr=0;
	wr=1;
}