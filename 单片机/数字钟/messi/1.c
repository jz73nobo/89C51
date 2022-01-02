#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
uchar num,num1,messi,crespo,kobe,hour1,hour2,minute1,minute2,second1,second2;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void display(uchar hour1,uchar hour2,uchar minute1,uchar minute2,uchar second1,uchar second2);
void init()
{
	wela=0;
	dula=0;
	num1=0;
	messi=0;
	crespo=0;
	EA=1;//开总中断	
	TR0=1;//启动定时器0中断
	ET0=1;//开定时器0中断
	TMOD=0x01;//定时器0工作方式1
	TH0=(65536-50000)/256;//定时器为50ms
	TL0=(65536-50000)%256;
}
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
		if(num1==20)
		{
			num1=0;
			messi++; 
			second1=messi/10;
			second2=messi%10;
			if(messi==59)
			{	
				crespo++;
				messi=0;
				minute1=crespo/10;
				minute2=crespo%10;
				if(crespo==59)
				{
					crespo=0;
					kobe++;
					hour1=kobe/10;
					hour2=kobe%10;
					if(kobe==23)
						kobe=0;
				}
			}
		}
		display(hour1,hour2,minute1,minute2,second1,second2);		
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;//定时器为50ms
	TL0=(65536-50000)%256;
	num1++;	
}
void display(uchar hour1,uchar hour2,uchar minute1,uchar minute2,uchar second1,uchar second2)
{
	dula=1;
	P0=table[hour1];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delay(1);

	dula=1;
	P0=table[hour2];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delay(1);

	dula=1;
	P0=table[minute1];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delay(1);

    dula=1;
	P0=table[minute2];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xf7;
	wela=0;
	delay(1);

	dula=1;
	P0=table[second1];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xef;
	wela=0;
	delay(1);

	dula=1;
	P0=table[second2];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xdf;
	wela=0;
	delay(1);
}
	