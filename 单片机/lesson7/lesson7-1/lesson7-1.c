#include<reg52.h>
void main()
{
	REN=1;
	SM0=0;
	SM1=1;
	TMOD=0x20;//设置定时器1为工作方式1
	TL1=0xfd;
	TH1=0xfd;
	TR1=1;
	EA=1;
	ES=1;
	while(1)
	{
	
	}
}
void ser() interrupt 4
{
	RI=0;
	P1=SBUF;	
}
