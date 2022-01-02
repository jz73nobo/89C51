#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit beep=P3^7;
uchar num,num1,hour1,hour2,minute1,minute2,second1,second2,mode,temp,aa,hour10,hour20,minute10,minute20,second10,second20;
long int messi,cao;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar keyscan();
void display2(uchar aa);
void display(uchar hour1,uchar hour2,uchar minute1,uchar minute2,uchar second1,uchar second2);
void display1(uchar hour10,uchar hour20,uchar minute10,uchar minute20,uchar second10,uchar second20);
void zd_clock();
void delay(uint z)
{
	uint t1,y;
	for(t1=z;t1>0;t1--)
		for(y=110;y>0;y--);
}
void init()
{	
	wela=0;
	dula=0;
	num1=0;
	cao=86400;
	messi=0;
	EA=1;//开总中断	
	TR0=1;//启动定时器0中断
	ET0=1;//开定时器0中断
	TMOD=0x01;//定时器0工作方式1
	TH0=(65536-50000)/256;//定时器为50ms
	TL0=(65536-50000)%256;
}
void main()
{
	init();	
	
	while(1)
	{	 display2(keyscan());
		if(num1==20)
		{	
			num1=0;
			messi++; 
			if(messi==86400)
				messi=0;
			hour1=messi/36000;
			hour2=messi%36000/3600;
			minute1=messi%3600/600;
			minute2=messi%3600%600/60;
			second1=messi%60/10;
			second2=messi%10;
			
			hour10=cao/36000;
			hour20=cao%36000/3600;
			minute10=cao%3600/600;
			minute20=cao%3600%600/60;
			second10=cao%60/10;
			second20=cao%10;	
		} 
		zd_clock();
		if(mode%2==1)
		{
			display1(hour10,hour20,minute10,minute20,second10,second20);  
		}
		else
		{	
			display(hour1,hour2,minute1,minute2,second1,second2);
		}
		
	
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
void display1(uchar hour10,uchar hour20,uchar minute10,uchar minute20,uchar second10,uchar second20)
{
	dula=1;
	P0=table[hour10];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delay(1);

	dula=1;
	P0=table[hour20];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delay(1);

	dula=1;
	P0=table[minute10];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delay(1);

    dula=1;
	P0=table[minute20];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xf7;
	wela=0;
	delay(1);

	dula=1;
	P0=table[second10];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xef;
	wela=0;
	delay(1);

	dula=1;
	P0=table[second20];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xdf;
	wela=0;
	delay(1);
}
void display2(uchar aa)
{
			dula=1;
			P0=table[aa];
			dula=0;		
}
uchar keyscan()
{
	P3=0xfe;
	temp=P3;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
			delay(10);
			temp=P3;
			temp=temp&0xf0;
			while(temp!=0xf0)
			{
				temp=P3;
				switch(temp)
				{
					case 0xee: messi=messi+1;
						break;
					case 0xde: messi=messi+60;
						break;
					case 0xbe: messi=messi+3600;
						break;
					case 0x7e: cao=cao-1;
						break;
				}
				 while(temp!=0xf0)
						{
							temp=P3;
							temp=temp&0xf0;
						}
			}
	}
		P3=0xfd;
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
				{
					delay(10);
					temp=P3;
					temp=temp&0xf0;
					while(temp!=0xf0)
					{
						temp=P3;
					switch(temp)
						{
							case 0xed:cao=cao-60;
								break;
							case 0xdd:cao=cao-3600;
								break;
							case 0xbd:mode++;
								break;
							case 0x7d:messi=messi+10;
								break;
						}
						while(temp!=0xf0)
							{
								temp=P3;
								temp=temp&0xf0;
							}
					}
		P3=0xfb;
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
				{
					delay(5);
					temp=P3;
					temp=temp&0xf0;
					while(temp!=0xf0)
					{
						temp=P3;
					switch(temp)
						{
							case 0xeb:messi+600;
								break;
							case 0xdb:messi+36000;
								break;
							case 0xbb:cao-10;
								break;
							case 0x7b:cao-600;
								break;
						}
					while(temp!=0xf0)
						{
							temp=P3;
							temp=temp&0xf0;
						}
					}
				}


			P3=0xf7;
			temp=P3;
			temp=temp&0xf0;
			while(temp!=0xf0)
			{
				delay(5);
				temp=P3;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
					temp=P3;
					switch(temp)
					{
						case 0xe7:cao-3600;
							break;
						case 0xd7:;
							break;
						case 0xb7:;
							break;
						case 0x77:;
							break;
					}
					while(temp!=0xf0)
					{
						temp=P3;
						temp=temp&0xf0;
					}
				}
			}
	}
}
void zd_clock() //整点报时函数
{
	if((messi>cao)&(messi<cao+60))
	{
		beep=0;
		delay(1);
		beep=1;
		delay(1);
	}
}