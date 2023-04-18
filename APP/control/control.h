#ifndef __CONTROL_H
#define __CONTROL_H
#include "system.h"



void EXTI9_5_IRQHandler(void);
int balance_UP(float Angle,float Mechanical_balance,float Gyro);
int velocity(int encoder_left,int encoder_right,int target);
int Turn_UP(int gyro_Z, int RC);

extern float pitch,roll,yaw; 								  			 //ŷ����(��̬��)
extern short aacx,aacy,aacz;													 //���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;											 //������ԭʼ����
extern float Encoder_Left,Encoder_Right;         		 //���ұ��������������
extern int Moto1,Moto2;												 //������������ո��������PWM




#endif
