#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
uchar temp,num,aa;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delay(uint z);
void main()
{
	num=1;
	aa=0;
	TMOD=0x01;//设置定时器/计数器
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//给定时器初值
	EA=1;//开总定时器/计数器中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器/计数器0
	temp=0xfe;
	P1=temp;//流水灯赋初值
	dula=1;
	P0=table[0];
	dula=0;//给数码管赋初值
	wela=1;
	P0=0xc0;
	wela=0;//全部点亮
	while(1)
	{
		delay(1000);//延时
		temp=_crol_(temp,1);
		P1=temp; //流水
	}
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;
	if(aa==40)
			{
				aa=0;
				dula=1;
				P0=table[num];
				dula=0;
				num++;
					if(num==16)
					{
						 num=0;
					}
			} //数码管
}