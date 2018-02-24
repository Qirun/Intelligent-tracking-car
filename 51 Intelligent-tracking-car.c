#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit lgo=P0^0;
sbit lback=P0^1;
sbit rgo=P0^2;
sbit rback=P0^3;	//如此设置后，lgo,lback控制左轮。 r控制右轮同理。对应L298N驱动模块上的IN1~IN4.

sbit r=P1^0;			//右侧寻迹模块信号脚口
sbit m=P1^1;		    //中间寻迹模块信号脚口
sbit l=P1^2;			//左侧侧寻迹模块信号脚口  三个红外探测器的信号接收脚口（DO脚口），接收到返回信号是为低电平，反之则反。
sbit ledqian=P2^6;
sbit ledhou=P2^5;
sbit ledzuo=P2^7;
sbit ledyou=P2^4;	//前后左右指示灯
uchar k=0;			//此参数使小车跑出轨道后，重新归位
uchar zkb1=0;
uchar zkb2=0;//分别控制左轮和右轮

uchar n=0; //定时器参数

void qianjin()
{
	zkb1=50;
	zkb2=50;
}

/*void tingzhi()
{
	zkb1=0;
	zkb2=0;	
}	  */

void xiaozuozhuan()
{
	zkb1=20;
	zkb2=45;
}

void xiaoyouzhuan()
{
	zkb1=40;
	zkb2=10;
}

void dazuozhuan()
{
	zkb1=10;
	zkb2=45;
}

void dayouzhuan()
{
	zkb1=50;
	zkb2=5;
}

void initT()
{
	TMOD=0x02;//定时器T0 方式2自动重装
	TH0=156/256;
	TL0=156%256;
	TR0=1;
	ET0=1;
	EA=1;
}

/*void init()
{
	ledqian=1;
	ledhou=1;
	ledzuo=1;
	ledyou=1;	
} */

void main()
{
	P2=0x00;
	initT();
	lback=0;
	rback=0;
	while(1)
	{
		unsigned char flag;
		if((l==0)&&(m==1)&&(r==0))
		{
			flag=1;k=1;//qianjin();
		}
	
		if ((l==0)&&(m==0)&&(r==1))
		{
			flag=2;k=2;//dayouzhuan();
		}
		if((l==0)&&(m==1)&&(l==1))
		{
			flag=3;k=3;//xiaoyouzhuan();
		}
		if((l==1)&&(m==0)&&(r==0))
		{
			flag=4;k=4;//dazuozhuan();
		}
		if((l==1)&&(m==1)&&(r==0))
		{
			flag=5;k=5;//xiaozuozhuan();
		}
		if(((m==0)&&(l==0)&&(r==0)))
		{
			flag=k;
		} 
		switch(flag)  
    	{  
	        case 1:qianjin();break;
			
			//case 2:tingzhi();break;   
	          
	        case 2:dayouzhuan();break;  
	          
	        case 3:xiaoyouzhuan();break;  
	          
	        case 4:dazuozhuan();break;  
	
		case 5:xiaozuozhuan();break;
	          
	        default:qianjin();break;  
    	}  
	}
}

void int0() interrupt 1
{
	n++;
	if(n<zkb1)
	lgo=1;		
	else lgo=0;
	if(n<zkb2)
	rgo=1;
	else rgo=0;
	if (n>50)
	n=0;	
}


