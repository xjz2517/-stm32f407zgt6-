#include "motor.h"
//������ƶ˿ڳ�ʼ������
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//���ģʽ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//�ܽ�����
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//�ٶ�Ϊ100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	AIN1=0,AIN2=0;
	BIN1=0,BIN2=0;
}
/**************************************************************************
�������ܣ�����ת���ƣ�ռ�ձȿ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	if(moto1<0)			AIN2=1,			AIN1=0;
	else 	          AIN2=0,			AIN1=1;
	PWMA=myabs(moto1);
	if(moto2<0)	BIN1=0,			BIN2=1;
	else        BIN1=1,			BIN2=0;
	PWMB=myabs(moto2);	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
Ŀ    �ģ�PWM�п���Ϊ��ֵ����ֻ�ܸ�����ʱ��PWM�Ĵ���ֻ������ֵ������Ҫ��PWM���о���ֵ����
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{
	 //===PWM������8400 ������8200
    if(Moto1<-8200 ) Moto1=-8200 ;
		if(Moto1>8200 )  Moto1=8200 ;
	  if(Moto2<-8200 ) Moto2=-8200 ;
		if(Moto2>8200 )  Moto2=8200 ;
}
