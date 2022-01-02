#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,
0x76,0x79,0x38,0x3f,0};
uchar temp,t0,t1,bai,shi,ge,flag,flag1;
uint shu;
void init();
void display(uchar,uchar,uchar,uchar,uchar,uchar);
void delay(uint z)
{
	uint t1,y;
	for(t1=z;t1>0;t1--)
		for(y=110;y>0;y--);
}
void main()
{
	init();
	while(1)
	{
		if(flag1!=1)
			display(7,6,5,bai,shi,ge);
		else
			display(16,17,18,18,19,20);	
	}
}

void init()
{
	shu=432;
	temp=0xfe;
	P1=temp;
	TMOD=0x11;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;
	ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
}

void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t0++;
	if(flag!=1)
		{
		if(t0==10)
			{
				t0=1;
				temp=_crol_(temp,1);
				P1=temp;
			}
		}
	else
		{
			if(t0%4==0)
				P1=~P1;
			if(t0==60)
			{
				TR0=0;
				P1=0xff;
				flag1=1;
			}
		}	
}

void timer1() interrupt 3
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	t1++;
	if(t1==2)
		{
			t1=0;
			shu--;
			bai=shu/100;
			shi=shu%100/10;
			ge=shu%10;
			if(shu==398)
				{
					TR0=0;
					TH0=(65536-50000)/256;
					TL0=(65536-50000)%256;
					TR0=1;
					flag=1;
					t0=0;
					P1=0xff;
					TR1=0;
				}	
		}	
}

void display(uchar aa,uchar bb,uchar cc,uchar ba,uchar sh,uchar g)
{
        dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xfe;
		wela=0;
		delay(1);

       	dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xfd;
		wela=0;
		delay(1);

       dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xfb;
		wela=0;
		delay(1);
        dula=1;
		P0=table[ba];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xf7;
		wela=0;
		delay(1);

		dula=1;
		P0=table[sh];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xef;
		wela=0;
		delay(1);

		dula=1;
		P0=table[g];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xdf;
		wela=0;
		delay(1);
}
