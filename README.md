# brushness_controller
无刷电机控制器。  
没有经过电调，用三极管搭建的三路半桥控制。  
![brushness_controller.jpg](https://github.com/nicekwell/brushness_controller/raw/master/brushness_controller.jpg)

视频：
控制云台无刷电机：<http://v.youku.com/v_show/id_XMTg5Nzc2ODIxNg==.html>
控制飞行器无刷电机（转不起来）：<http://v.youku.com/v_show/id_XMTg5Nzc3MjgzNg==.html>

# 功能
上方是三路半桥，每路的上三极管和下三极管的导通都受单片机控制（总共6个控制脚）。  
下方是5个按键，从左到右功能依次是：  
速度-1，左方向步进一步，停止，右方向步进一步，速度+1

两个步进控制是有方向的，速度控制没有方向控制功能（类似于电调）。

上方的led灯是和单片机引脚硬件相连的，高电平点亮，用于指示各路半桥的上、下三极管导通状态。

# 硬件
【单片机】stc89c52  
【晶振】12MHz  
【引脚连接】

功能 | 引脚 | 备注
:-: |:-: |:-: |
u相的上三极管 | P0.0 | 高电平导通 
u相的下三极管 | P0.1 | 高电平导通 
v相的上三极管 | P0.2 | 高电平导通 
v相的下三极管 | P0.3 | 高电平导通 
w相的上三极管 | P0.4 | 高电平导通 
w相的下三极管 | P0.5 | 高电平导通 
速度-1按键 | P1.0 |	按下是低电平
左方向步进一步 | P1.1 |	按下是低电平
停止 | P1.2 | 按下是低电平
右方向步进一步 | P3.4 |	按下是低电平
速度+1按键 | P3.7 |	按下是低电平


