#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
uchar temp,aa;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar code tablewe[]={
0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
void delay(uint z);
void init();
void main()
{
	init();
	while(1)
	{
		wela=1;
		P0=table[temp];
		temp++;
		wela=0;
		if(temp==6)
		temp=0;
		delay(1000);
		
		dula=1;
		P0=table[aa];
		aa++;
		dula=0;
		if(aa==6);
		aa=0;
		delay(1000);			
	}
}
void init()
{
	temp=0;
	aa=0;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;	
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--); 
}