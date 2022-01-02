#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit dula=P2^6;
sbit wela=P2^7;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
 void write_date(uchar date)
{
	lcdrs=1;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init()
{
	dula=0;
	wela=0;
	lcden=0;
	write_com(0x01);
	write_com(0x38);
	write_com(0x0f);
}
void main()
{	  void init();
  write_com(0x38);
	write_com(0x0f);
}
