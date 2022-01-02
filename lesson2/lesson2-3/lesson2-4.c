#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp;		  
void delay(uint z);
void main()
{	
	temp=0xfe;
	P1=temp;
		while(1)
		{
		 	
			temp=_crol_(temp,1);
			delay(300);
			P1=temp;
		}
 
}
void delay(z)
{
	for(x=100;x>0;x--)
	{
		  for(y=z;y>0;y--)
		  {

		  };
	};
}