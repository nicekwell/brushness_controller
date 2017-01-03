#include <reg52.h>

sbit u_up=P0^0;
sbit u_down=P0^1;
sbit v_up=P0^2;
sbit v_down=P0^3;
sbit w_up=P0^4;
sbit w_down=P0^5;

sbit key_speed_m1=P1^0;
sbit key_speed_p1=P3^7;
sbit key_step_m1=P1^1;
sbit key_step_p1=P3^4;
sbit key_stop=P1^2;

unsigned char f = 0;	//切换频率，一秒钟自动切换多少次
unsigned char T;	//周期，每隔多长时间切换一次，和f对应，单位是5ms
void setf(unsigned char f)
{
    double T_temp;
    if(f != 0)
    {
	T_temp = (1/(double)f) * 200;
	T = (unsigned char)T_temp;
    }
}

unsigned char code list[6][6] = {
    {0, 1, 1, 0, 0, 0},	//v-->u
    {0, 0, 1, 0, 0, 1},	//v-->w
    {1, 0, 0, 0, 0, 1},	//u-->w
    {1, 0, 0, 1, 0, 0},	//u-->v
    {0, 0, 0, 1, 1, 0},	//w-->v
    {0, 1, 0, 0, 1, 0},	//w-->u
};
unsigned char step=0;	//0~5

void step_forward()
{
    step++;
    if(step == 6)
	step=0;
    u_up = list[step][0];
    u_down = list[step][1];
    v_up = list[step][2];
    v_down = list[step][3];
    w_up = list[step][4];
    w_down = list[step][5];
}
void step_back()
{
    step--;
    if(step == 0xff)
	step=5;
    u_up = list[step][0];
    u_down = list[step][1];
    v_up = list[step][2];
    v_down = list[step][3];
    w_up = list[step][4];
    w_down = list[step][5];
}

void delay5(unsigned char n)
{
	unsigned int i;
	for(;n>0;n--)
		for(i=624;i>0;i--);
}

void main()
{
    step_forward();
    step_forward();
    f = 0;
    setf(f);
    while(1)
    {
	delay5(1);
	{
	    static key_step_m1_last=1, key_step_p1_last=1, key_speed_m1_last, key_speed_p1_last, key_stop_last;;
	    if(key_step_m1_last == 1 && key_step_m1 ==0)
	    {
		step_back();
	    }
	    else if(key_step_p1_last == 1 && key_step_p1 == 0)
	    {
		step_forward();
	    }
	    else if(key_speed_m1_last == 1 && key_speed_m1 == 0)
	    {
		if(f != 0)
		{
		    f--;
		    setf(f);
		}
	    }
	    else if(key_speed_p1_last == 1 && key_speed_p1 == 0)
	    {
		if(f != 200)
		{
		    f++;
		    setf(f);
		}
	    }
	    else if(key_stop_last == 1 && key_stop == 0)
	    {
		f=0;
		setf(f);
	    }
	    key_step_m1_last=key_step_m1;
	    key_step_p1_last=key_step_p1;
	    key_speed_m1_last = key_speed_m1;
	    key_speed_p1_last = key_speed_p1;
	    key_stop_last = key_stop;
	}
	{	//设置速度控制进程
	    static unsigned char num=0;
	    if(f)
	    {
		num++;
		if(num >= T)
		{
		    num = 0;
		    step_forward();
		}
	    }
	}
    }
}
