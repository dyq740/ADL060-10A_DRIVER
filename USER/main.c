#include "sys.h"
#include "delay.h"
#include "can.h"
#include "timer2.h"
#include "led.h"
#include "YTCH_Driver.h"

int main(void)
{ 
	unsigned short statusword;
	int target_position = 2000;
	int motor_position;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();    //��ʼ����ʱ����
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_9tq,6,CAN_Mode_Normal);//CAN��ʼ����ͨģʽ,������500kbps    //CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
  TIM2_Init(9,7199);	//��ʱ��2ʱ��84M����Ƶϵ��8400��84M/84=1M ���Լ���1000��Ϊ0.1ms,�����ظ���ʱ���

	delay_ms(100);
	LED_Init();
 	Switch_Driver_Mode(2,PROFILE_VELOCITY_MODE);
	delay_ms(10);
	Switch_Driver_Mode(1,PROFILE_POSITION_MODE);
	Enable_Driver(2);
	delay_ms(10);
	Enable_Driver(1);
	delay_ms(10);
	PVM_Set_Speed(2,3000);
	delay_ms(10);
	PPM_Set_Position(1,target_position,1);
	delay_ms(100);
	
	LED1=0;
	
while(1)
	{	
		if(Read_Statusword(1,&statusword) == 0) //��ȡ�ɹ�
		{
			if(statusword & TARGET_REACHED_BIT) // ����ָ��λ��
			{
				Read_Position(1,&motor_position);
				delay_ms(100);
				LED1=~LED1;
				PPM_Set_Position(1,target_position,1); // ����λ��
				target_position = target_position *(-1);
				//delay_us(10000);	
      } 
    }	
		//Read_Statusword(2,&statusword);
	} 
	
}

