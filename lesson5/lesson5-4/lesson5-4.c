#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit wela=P2^7;
sbit dula=P2^6;
sbit d1=P1^0;
sbit key1=P3^4;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar num;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	wela=1;
	P0=0xfe;
	wela=0;
	P3=0xff;
	while(1)
	{
		if(key1==0)
		{
		delay(10);
			if(key1==0)
			{
			num++;
			if(num==10)
			num=0;
			while(!key1==0);
			delay(10);
			while(!key1==0);
			d1=0;
			}
		}
		else
			d1=1;
			dula=1;
			P0=table[num];
			dula=0;
				
	}
}