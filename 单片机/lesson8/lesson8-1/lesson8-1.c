#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit dula=P2^6;
sbit wela=P2^7;
uchar num;
uchar code table[]="leo messi argentina" ;
uchar code table1[]="zhangjinyuan china" ;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=100;y>0;y--);
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
 void write_data(uchar dat)
{
	P0=dat;
	lcdrs=1;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init()
{
	lcden=0;
	wela=0;
	dula=0;
	write_com(0x38);
	write_com(0x0f);
	write_com(0x06);
}
void main()
{
	init();
	for(num=0;num>19;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x01);
	write_com(0x80+0x40); 
	for(num=0;num>18;num++)
	{
		write_data(table1[num]);
		delay(20);
	} 
	while(1);
}
