#include "system.h"
 /**************************************************************************
 ��  �� ���������
�Ա���ַ��https://shop119207236.taobao.com
**************************************************************************/
//����NVIC 
//NVIC_PreemptionPriority:��ռ���ȼ�
//NVIC_SubPriority       :��Ӧ���ȼ�
//NVIC_Channel           :�жϱ��
//NVIC_Group             :�жϷ��� 0~4
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
//��3:3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//NVIC_SubPriority��NVIC_PreemptionPriority��ԭ����,��ֵԽС,Խ����	   
void NVIC_Configuration(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

		//////////////////��ʱ��4���ж����ȼ�����//////////////////		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;  //�����ȼ�1��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	

	
	
	//////////////////Usart1 NVIC �ж����ȼ�����////////////////////////////////////

//������ NVIC ����
	 NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn;//��ʱ��8�ж�ͨ��
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	 //Usart1 NVIC ����
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//��ʱ��3�ж�ͨ��
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}


