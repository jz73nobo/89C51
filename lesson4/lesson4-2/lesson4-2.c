#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
uchar temp,numdu,numwe,aa;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar code tablewe[]={
0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
void delay(uint z);
void main()
{
	numdu=0;
	numwe=0;
	aa=0;
	TMOD=0x01;//设置定时器/计数器
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//给定时器初值
	EA=1;//开总定时器/计数器中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器/计数器0
	while(1)
	{
		
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;
	if(aa==20)
	{
		aa=0;
		numdu++;
		if(numdu==7)
			numdu=1;
		dula=1;
		P0=table[numdu];
		dula=0;
		wela=1;
		P0=tablewe[numwe];
		wela=0;		
		numwe++;
		if(numwe==6)
			numwe=0;
	}
}