#include<reg52.h>
sbit D1=P1^0;
unsigned int a;
void main()
{
	while(1)
	{
		a=50000;
		D1=0;
		while(a--);
		a=50000;
		while(a--);
		a=50000;
		D1=1;
		while(a--);
	}
}