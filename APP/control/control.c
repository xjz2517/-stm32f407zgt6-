#include "control.h"
#include "usart.h"	
#include <MPU6050.h>
#include "system.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

int Balance_Pwm,Velocity_Pwm,Turn_Pwm,Turn_Kp;

float Target_Speed=0;	//�����ٶȣ������������ڿ���С��ǰ�����˼����ٶȡ�
float Turn_Speed=0;		//�����ٶȣ�ƫ����

float balance_UP_KP=330;//550; 	 // С��ֱ����PD����
float balance_UP_KD=1.02;

float velocity_KP=105;     // С���ٶȻ�PI����
float velocity_KI=0.525;
 
float Turn_Kd=TURN_KD;//ת��KP��KD
float Turn_KP=TURN_KP;

float Mechanical_angle=0; 





/*******************************************************************************
* �� �� ��         : EXTI0_IRQHandler
* ��������		   : �ⲿ�ж�0����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==1)
	{
		
		mpu_dmp_get_data(&pitch,&roll,&yaw);										 //�õ�ŷ���ǣ���̬�ǣ�������
		MPU6050_Get_Gyroscope(&gyrox,&gyroy,&gyroz);								 //�õ�����������
		Led_Flash(100);
		
		
		
		
		


		Encoder_Right= Read_Encoder(2); 
		Encoder_Left =-Read_Encoder(3);
		
		Balance_Pwm =balance_UP(roll,Mechanical_angle,gyrox);   							//===ֱ����PID����	
	  Velocity_Pwm=velocity(Encoder_Left,Encoder_Right,Target_Speed);       //===�ٶȻ�PID����	 
		//Turn_Pwm =Turn_UP(gyroz,Turn_Speed);        													//===ת��PID����
		
		
		Moto1=Balance_Pwm+Velocity_Pwm;//+Turn_Pwm;  	            	//===�������ֵ������PWM
		Moto2=Balance_Pwm+Velocity_Pwm;//-Turn_Pwm;                  //===�������ֵ������PWM

		
		Xianfu_Pwm();  				 																	  //===PWM�޷�
		Set_Pwm(Moto1,Moto2);                                     //===��ֵ��PWM�Ĵ���
		
		
		
		}
    EXTI_ClearITPendingBit(EXTI_Line0);	
	}
	



/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ���еƽ��Ƕȣ���е��ֵ�������ٶ�
����  ֵ��ֱ������PWM
��    �ߣ��������
**************************************************************************/
int balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
   float Bias;
	 int balance;
	
	 Bias=Angle-Mechanical_balance;
	 balance=balance_UP_KP*Bias+balance_UP_KD*Gyro;  //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	 return balance;
}

/**************************************************************************
�������ܣ��ٶ�PI����
��ڲ����������������ֵ
����  ֵ���ٶȿ���PWM
��    �ߣ��������
**************************************************************************/
int velocity(int encoder_left,int encoder_right,int Target_Speed)
{  
    static float Velocity,Encoder_Least,Encoder;
	  static float Encoder_Integral;
   //=============�ٶ�PI������=======================//	
    Encoder_Least=(Encoder_Left+Encoder_Right)-Target_Speed;//-target;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶ� 
		Encoder *= 0.8f;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.2f;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
		//Encoder_Integral=Encoder_Integral - Target_Speed;                       //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
		if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===�����޷�	
		Velocity=Encoder*velocity_KP+Encoder_Integral*velocity_KI;        //===�ٶȿ���	
	  if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===����رպ��������
	  return Velocity;
}
/**************************************************************************
�������ܣ�ת��PD����
��ڲ����������������ֵ��Z����ٶ�
����  ֵ��ת�����PWM
��    �ߣ��������
**************************************************************************/

int Turn_UP(int gyro_Z, int RC)
{
	int PWM_out;
		/*ת��Լ��*/
	if(RC==0)Turn_Kd=TURN_KD;//��������ת��ָ�����ת��Լ��
	else Turn_Kd=0;//������ת��ָ����յ�����ȥ��ת��Լ��
	
	PWM_out=Turn_Kd*gyro_Z + Turn_KP*RC;
	return PWM_out;
}


















