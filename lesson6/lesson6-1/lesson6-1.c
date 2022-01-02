#include <reg52.h>
sbit csda=P3^2;
sbit wr=P3^6;
void main()
{
	csda=0;
	wr=0;
	P0=0xff;
	while(1);
}