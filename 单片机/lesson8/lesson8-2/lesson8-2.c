#include<reg52.h>
#define uchar unsigned char 
sbit sda=P2^0;
sbit scl=P2^1;
void delay()
{
	
}
void start()
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
} 
void stop()
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}
void main()
{	

}