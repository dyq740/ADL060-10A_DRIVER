#include "sys.h"
#include "delay.h"
#include "can.h"
#include "timer2.h"
#include "YTCH_Driver.h"

int main(void)
{ 
	unsigned short statusword;
	int target_position = 200000;
	int motor_position;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();    //初始化延时函数
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_3tq,6,CAN_Mode_Normal);//CAN初始化普通模式,波特率1Mbps    //CAN工作模式;0,普通模式;1,环回模式
  TIM2_Init(9,7199);	//定时器2时钟84M，分频系数8400，84M/84=1M 所以计数1000次为0.1ms,用作回复超时检测

	delay_ms(100);
 	Switch_Driver_Mode(1,PROFILE_POSITION_MODE);
	Enable_Driver(1);
	delay_ms(100);
	PPM_Set_Position(1,target_position,1);
	
while(1)
	{	
		if(Read_Statusword(1,&statusword) == 0) //读取成功
		{
			if(statusword & TARGET_REACHED_BIT) // 到达指定位置
			{
				Read_Position(1,&motor_position);
				delay_ms(100);
				PPM_Set_Position(1,target_position,1); // 绝对位置
				target_position = target_position *(-1);
				//delay_us(10000);	
      } 
    }	
	} 
	
}