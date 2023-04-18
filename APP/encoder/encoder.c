//��������ʼ��
/*�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����*/


#include "encoder.h"
void Encoder_Init_TIM8(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//ʹ�ܶ�ʱ��8��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��PA�˿�ʱ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);//�ܽŹ��ܸ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�PC6,PC7����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//����ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);//��������Ӧ�˿ڳ�ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);  //���ṹ����Ĭ��ֵ���
  TIM_TimeBaseInitStructure.TIM_Period=ENCODER_TIM_PERIOD;; //�Զ�װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler=0x0; //��Ƶϵ��������Ƶ
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM8,&TIM_ICInitStructure);
  TIM_ClearFlag(TIM8,TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
  //Reset counter
  TIM_SetCounter(TIM8,0);
  TIM_Cmd(TIM8,ENABLE); 

}


/**************************************************************************
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��2��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);//�ܽŹ��ܸ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�PA6,PA7����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//����ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��������Ӧ�˿ڳ�ʼ��
	TIM_TimeBaseStructInit (&TIM_TimeBaseInitStructure);  //���ṹ����Ĭ��ֵ���
  TIM_TimeBaseInitStructure.TIM_Period=ENCODER_TIM_PERIOD;; //�Զ�װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler=0x0; //��Ƶϵ��������Ƶ
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	//TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3,TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE); 

}
/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/*�������ܣ�TIM3�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001)//����ж�
	{
   TIM3->SR&=~(1<<0);//����жϱ�־λ 			
	}				   
	    
}
/**************************************************************************
�������ܣ�TIM8�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM8->SR&0X0001)//����ж�
	{
   TIM8->SR&=~(1<<0);//����жϱ�־λ		
	}				   
	 	    
}







