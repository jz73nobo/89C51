#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit beep=P2^3;
uchar temp;
void delay(uint z);
void main()
{
	temp=0xfe;
	P1=temp;
	beep=0;
		while(1)
		{
			delay(300);
			temp=_crol_(temp,1);
			P1=temp;	
		}
} 
void delay(z)
{
	uint x,y;
		for(x=200;x>0;x--)
		{
		 	for(y=z;y>0;y--)
			{

			};
		};

}