#include<reg52.h>
sbit wela=P2^7;
sbit dula=P2^6;
void main()
{
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=0x06;
	wela=0;
	while(1);
}