#include "pwm.h"

/*******************************************************************************
* �� �� ��         : TIM2_CH1_PWM_Init
* ��������		   : TIM2ͨ��1 PWM��ʼ������
* ��    ��         : per:��װ��ֵ
					 psc:��Ƶϵ��
* ��    ��         : ��
PWMƵ��=per+psc+1/ʱ��Ƶ��
*******************************************************************************/
void TIM1_PWM_Init(u16 per,u16 psc)
{
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//ʹ��TIM1ʱ��,����APB2��168MHz
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);//�ܽŸ���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_11;//�ܽ�����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//�ٶ�Ϊ100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ���ṹ��
	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	//TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	//TIM_OCInitStructure.TIM_Pulse = per>>1;
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure); //����Ƚ�ͨ��1��ʼ��
	TIM_OC4Init(TIM1,&TIM_OCInitStructure); //����Ƚ�ͨ��1��ʼ��
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1,ENABLE);//ʹ��Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1,ENABLE); //ʹ�ܶ�ʱ��
		
}


