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
    P0=0;
    while(1)
    {
	delay5(1);
	{
	    static key_step_m1_last=1, key_step_p1_last=1;
	    if(key_step_m1_last == 1 && key_step_m1 ==0)
	    {
		step_back();
	    }
	    if(key_step_p1_last == 1 && key_step_p1 == 0)
	    {
		step_forward();
	    }
	    key_step_m1_last=key_step_m1;
	    key_step_p1_last=key_step_p1;
	}
    }
}
