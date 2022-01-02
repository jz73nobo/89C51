#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
sbit d1=P1^0;
uchar num;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delay(uint z);
void main()
{	
	TMOD=0x01;//设置定时器0为工作方式1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	TRO=1;//启动定时器0
	d1=1;
	wela=1;
	P0=0xea;//11110101
	wela=0;
	int tt;
	while(1)
	{
		if(tt=20)
		{
		tt=0;
		num++;
		dula=1;
		P0=table[num];
		dula=0;
		delay(1000);
		}
	
	}

}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void exter0() interrupt 1
{
 	d1=0;
} 
