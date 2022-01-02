#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit dula=P2^6; //����ܶ�ѡ
sbit wela=P2^7; //�����λѡ
sbit fm=P2^3; //������
sbit s2=P3^4; //s2����,���õ�ʱ
sbit s3=P3^5; //s3����,��1
sbit s4=P3^6; //s4����,��1
sbit s5=P3^7; //s5����,�л���ʾ
sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
//sbit led4=P1^3;
//sbit led5=P1^4;
//sbit led6=P1^5;
//sbit led7=P1^6;
//sbit led8=P1^7;
uchar count;
uchar sec,minu,hour,day,week,mon;
uchar n_sec,n_minu,n_hour;
uint year;
uchar set_2=1,set_5=1;
uchar hs,hg,mis,mig,ss,sg;
uchar nhs,nhg,nms,nmg,nss=0,nsg=0;
uchar ms,mg,ds,dg,w;
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,
0x90,0x88,0x83,0xc6,0xa1,0x8e,0x86,0xbf}; //0~F,-,����
uchar code tableyi[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};//0-F,-,����
uchar code table_d[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,
0x87,0xff,0xef}; //0~9���飬��С����
uchar table1[]={31,31,29,31,30,31,30,31,31,30,31,30,31}; //����
uchar table2[]={31,31,28,31,30,31,30,31,31,30,31,30,31}; //������
void delay(uint); //��ʱ����
void timer0(); //��ʱ�жϺ���
void jishi(); //��ʱ����
void key_change(); //�л���ʾ��������
void key_set(); //����ʱ�䰴������
void disp(uchar,uchar,uchar,uchar,uchar,uchar); //��ʾ����
void zd_clock(); //���㱨ʱ����
void nz_clock(); //���Ӻ���
uchar incone(uchar); //��1����
uchar decone(uchar); //��1����
void set_time(); //����ʱ�亯��
void set_clock(); //�������Ӻ���
void set_mdw(); //�����������ں���

void main() //������
{
EA=1;
ET0=1;
TR0=1;
TMOD=0x01;
TH0=0x4c; //50ms��ֵ ����11.0592
TL0=0x00;
hour=23;minu=59;sec=49; //����ֵ��11��59��0��
n_hour=12;n_minu=56;n_sec=13; //���Ӹ���ֵ12��1��0��
year=2008;mon=5;day=14;week=3;//���������ڸ���ֵ2008��5��11�������죻ף��������ĸ�׽��տ���
while(1)
{
hs=hour/10; //ʱ����HH.MM.SS
hg=hour%10;
mis=minu/10;
mig=minu%10;
ss=sec/10;
sg=sec%10;

ms=mon/10; //����-����MM.DD.-W
mg=mon%10;
ds=day/10;
dg=day%10;
w=week;
nhs=n_hour/10; //���Ӷ�ʱHH.MM.SS
nhg=n_hour%10;
nms=n_minu/10;
nmg=n_minu%10;
nss=n_sec/10;
nsg=n_sec%10;
key_change(); //s5����ɨ��
key_set(); //s2����ɨ��
set_time(); //����ʱ��
set_mdw(); //������������
set_clock(); //��������


if(set_5==1) //������ʱ��ʾ
{
disp(hs,hg,mis,mig,ss,sg);
}
if(set_5==2) //����ʱ��,LED1����
{
disp(hs,hg,mis,mig,ss,sg);
if(sec%2==0)
{led2=1;led3=1;led1=~led1;}
// else
// {led1=1;}
}
if(set_5==3) //������ʾ����-����
{
disp(ms,mg,ds,dg,16,w);
}
if(set_5==4) //��������-����,LED2����
{
disp(ms,mg,ds,dg,16,w);
if(sec%2==0)
{led1=1;led3=1;led2=~led2;}

// else
// {led2=1;}
}

if(set_5==5) //������ʾ��ʱ
{
disp(nhs,nhg,nms,nmg,nss,nsg);
}
if(set_5==6) //�������Ӷ�ʱ,LED3����
{
disp(nhs,nhg,nms,nmg,nss,nsg);
if(sec%2==0)
{led1=1;led2=1;led3=~led3;}

// else
// {led3=1;}
}

zd_clock(); //���㱨ʱ
nz_clock(); //����
}

}
void timer0() interrupt 1 //50ms�жϺ���
{
TMOD=0x01;
TH0=0x4c; //50ms��ֵ ����11.0592
TL0=0x00;
count++;
if(count==20)
{
count=0;
sec++;
jishi(); //����ʱ����
}
}
void jishi() //��ʱ����
{
if(sec==60)
{
sec=0;
minu++;
if(minu==60)
{
minu=0;
hour++;
if(hour==24)
{ hour=0;
day++;
week++;
if(week==8)
{week=0;}
if(year%4==0&&year%100!=0||year%400==0) //����
{
if(day==table1[mon]+1)
{
day=0;
mon++;
if(mon==13)
{mon=0;year++;}
}
}
else //������
{
if(day==table2[mon]+1)
{
day=0;
mon++;
if(mon==13)
{mon=0;year++;}
}
}
}
}
}
}
void key_change() //s5����ɨ��
{
if(s5==0)
{
delay(200);
if(s5==0)
{
set_5++;
while(!s5);
if(set_5==7)
{set_5=1;}
}
}
}

void key_set() //s2����ɨ��
{
if(s2==0)
{
delay(10);
if(s2==0)
{
set_2++;
while(!s2);
if(set_2==4)
{set_2=1;}
}
}

}
void disp(uchar a1,uchar a2,uchar a3,uchar a4,uchar a5,uchar a6) //��ʾ����
{
dula=0;
P0=table[a1]; //������P0��
dula=1; //ѡ����ѡ
dula=0; //�ض�ѡ

wela=0;
P0=0x01; //λѡ(��1�������)��P0
wela=1; //ѡ��λѡ
wela=0; //��λѡ
delay(1); //��ʱһС��

dula=0;
P0=table[a2]; //��2���������ʾ,��С����
dula=1;
dula=0;

P0=0x02;
wela=1;
wela=0;
delay(1);

dula=0;
P0=table[a3]; //��3���������ʾ
dula=1;
dula=0;

wela=0;
P0=0x04;
wela=1;
wela=0;
delay(1);

P0=table[a4]; //��4���������ʾ,��С����
dula=1;
dula=0;

P0=0x08;
wela=1;
wela=0;
delay(1);

dula=0; //��5���������ʾ
P0=table[a5];
dula=1;
dula=0;

wela=0;
P0=0x10;
wela=1;
wela=0;
delay(1);

P0=table[a6]; //��6���������ʾ
dula=1;
dula=0;

P0=0x20;
wela=1;
wela=0;
delay(1);
}
void zd_clock() //���㱨ʱ����
{
if(minu==59&&(sec==53||sec==55||sec==57))
{
fm=0;
delay(1);
fm=1;
delay(1);
}
if(minu==59&&sec==59)
{
fm=0;
delay(1);
fm=1;
delay(1);
}
}
void nz_clock() //���Ӻ���
{
if(hour==n_hour&&minu==n_minu&&sec==n_sec)
if((sec%2==0)&&sec<30)
{
fm=0;
delay(20);
fm=1;
delay(20);
}
}
void set_time() //����ʱ�亯��
{
if(set_5==2)
{
if(set_2==1)
{
hour=incone(hour);
if(hour==24)
{hour=0;}
// if(hour<0)
// {hour=23;}
hour=decone(hour);


}
if(set_2==2)
{
minu=incone(minu);
if(minu==60)
{minu=0;}
// if(minu<0)
// {minu=59;}
minu=decone(minu);

}
}
}
void set_mdw() //�����������ں���
{
if(set_5==4)
{
if(set_2==1)
{
mon=incone(mon);
if(mon==13)
{mon=1;}
mon=decone(mon);
// if(mon==0)
// {mon=12;}
}
if(set_2==2)
{
day=incone(day);
if(day==32)
{day=0;}
day=decone(day);
// if(day==0)
// {day=0;}
}
if(set_2==3)
{
week=incone(week);
if(week==8)
{week=0;}
week=decone(week);
// if(week==0)
// {week=7;}
}
}
}
void set_clock() //�������Ӻ���
{
if(set_5==6)
{
if(set_2==1)
{
n_hour=incone(n_hour);
if(n_hour==24)
{n_hour=0;}
n_hour=decone(n_hour);
// if(n_hour==0)
// {n_hour=0;}
}
if(set_2==2)
{
n_minu=incone(n_minu);
if(n_minu==60)
{n_minu=0;}
n_minu=decone(n_minu);
// if(n_minu==0)
// {n_minu=0;}
}
}

}
uchar incone(uchar n) //��1����
{
if(s3==0)
{ delay(200);
if(s3==0)
{
n++;
while(!s3);
}
}
return(n);
}
uchar decone(uchar m) //��1����
{
if(s4==0)
{
delay(200);
if(s4==0)
{
m--;
while(!s4);
if(m<0)
{m=0;}
}
}

return(m);
}

void delay(uint k) //��ʱ����
{
uint i,j;
for(i=k;i>0;i--)
for(j=80;j>0;j--);
}