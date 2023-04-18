
#include "system.h"
float Encoder_Left,Encoder_Right;         		 //���ұ��������������
int Moto1=0,Moto2=0;												 //������������ո��������PWM

int i=0;
int main(void)	
{ 
  SysTick_Init(168);   	           //=====��ʱ������ʼ��	
	NVIC_Configuration();					 //=====�ж����ȼ�����
	USART1_Init(115200);          //=====����1��ʼ��
	LED_Init();                    //=====��ʼ���� LED ���ӵ�IO
	TIM1_PWM_Init(8400,0);     //=====��ʼ��PWM 10KHZ,�������������
  Encoder_Init_TIM8();					 //=====������2��ʼ��
	Encoder_Init_TIM3();					 //=====������3��ʼ��

	delay_ms(1000);								 //=====��ʱ1s ���С���ϵ�������ת������
	Motor_Init();									 //=====��ʼ���������ӵ�Ӳ��IO�ӿ� 
	TIM4_Init(100,8400-1);			 //=====10ms�ж�һ�Ρ����ȫ������ʱ���������ֵΪ90		
 // TIM4_Init(50,8400-1);			   //=====5ms�ж�һ�Ρ����ȫ������ʱ���������ֵΪ45
	 while(1)	
	{
		i++;
		if(i%20==0)
		{
			LED1=!LED1;
			printf("Encoder_Left=%.2f,Encoder_Right=%.2f\n",Encoder_Left,Encoder_Right);
		}
		delay_ms(10);
	}			
	}
	
