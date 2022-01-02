#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0};
uchar num,messi;
sbit key1=P3^4;
sbit dula=P2^6;
sbit wela=P2^7;
void delay(uint z)
{
	uint t1,y;
	for(t1=z;t1>0;t1--)
		for(y=110;y>0;y--);
}
void main()
{	
	dula=0;
	dula=1;
	P0=0;
	dula=0;
	wela=1;
	P0=0x00;
	wela=0;
	while(1)
	{	
		P3=0xfe;
		messi=P3;
		messi=messi&0xf0;
		while(messi!=0xf0)
		{
			delay(5);
			messi=P3;
			messi=messi&0xf0;
			while(messi!=0xf0)
			{
				messi=P3;
				switch(messi)
				{
					case 0xee: num=1;
						break;
					case 0xde: num=2;
						break;
					case 0xbe: num=3;
						break;
					case 0x7e:num=4;
						break;
				}
				 while(messi!=0xf0)
						{
							messi=P3;
							messi=messi&0xf0;
						}
				dula=1;
				P0=table[num];
				dula=0;
			}
		}	
	}		
}