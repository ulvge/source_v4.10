/*********************************************************************************

 
                                  ��ӡ������ͷ�ļ� 

���ܣ��ṩ��ӡ������ͷ�ļ�

���ߣ�

���ڣ�

�޸ļ�¼��




**********************************************************************************/



#ifndef __Sprint_H
#define __Sprint_H 1


#include "stm32f10x.h"


#define  NO_Paper     1


/***************************   ��ӡ���������Ŷ���       ***********************************/


#define  MOT1_SET()           GPIO_SetBits(GPIOC, GPIO_Pin_9)      //���������������

#define  MOT1_REST()          GPIO_ResetBits(GPIOC, GPIO_Pin_9)      //���������������

  


#define  MOT2_SET()           GPIO_SetBits(GPIOC, GPIO_Pin_8)      //���������������

#define  MOT2_REST()          GPIO_ResetBits(GPIOC, GPIO_Pin_8)      //���������������



#define  MOT3_SET()           GPIO_SetBits(GPIOC, GPIO_Pin_6)      //������������������˴���ԭ��ͼ�е�MOT3��MOT4���ţ�ע��

#define  MOT3_REST()          GPIO_ResetBits(GPIOC, GPIO_Pin_6)    //���������������	�˴���ԭ��ͼ�е�MOT3��MOT4���ţ�ע��


#define  MOT4_SET()           GPIO_SetBits(GPIOC, GPIO_Pin_7)      //��������������� �˴���ԭ��ͼ�е�MOT3��MOT4���ţ�ע��

#define  MOT4_REST()          GPIO_ResetBits(GPIOC, GPIO_Pin_7)     //���������������	�˴���ԭ��ͼ�е�MOT3��MOT4���ţ�ע��



#define  Sprint_LA_SET()      GPIO_SetBits(GPIOB, GPIO_Pin_12)      //��������
#define  Sprint_LA_REST()	    GPIO_ResetBits(GPIOB, GPIO_Pin_12)


#define  PR_DIN_SET()         GPIO_SetBits(GPIOB, GPIO_Pin_15)       //��ӡ�������
#define  PR_DIN_REST()        GPIO_ResetBits(GPIOB, GPIO_Pin_15)       //��ӡ�������



#define  PR_CLK_SET()         GPIO_SetBits(GPIOB, GPIO_Pin_13)       //��ӡ�������ʱ�� 

#define  PR_CLK_REST()        GPIO_ResetBits(GPIOB, GPIO_Pin_13)       //��ӡ�������ʱ��          


#define  STB1_SET()           GPIO_SetBits(GPIOB, GPIO_Pin_7)       //��ӡ��ѡ����
#define  STB1_REST()          GPIO_ResetBits(GPIOB, GPIO_Pin_7)       //��ӡ��ѡ����

#define  STB2_SET()           GPIO_SetBits(GPIOB, GPIO_Pin_6)       //��ӡ��ѡ����
#define  STB2_REST()          GPIO_ResetBits(GPIOB, GPIO_Pin_6)    //��ӡ��ѡ����

#define  STB3_SET()           GPIO_SetBits(GPIOB, GPIO_Pin_5)       //��ӡ��ѡ����
#define  STB3_REST()          GPIO_ResetBits(GPIOB, GPIO_Pin_5)    //��ӡ��ѡ����



#define  MotorDly       0x2200        //���������ʱ��������

#define  Hotup_Time     0x1400        //���ȴ�ӡ��ʱ��������




/****************************��ӡ�����*********************************/

//#define  Step_Delay        0x3fff        //���������ʱ��������


//#define  command_Sprint      0x1        //���������ʱ��������


/*********************   �ײ���������    ********************************************/

void Step_by_Step(void);//�����ߺ���



/***********************ֽ�����޺���***********************************************/ 

unsigned char  Paper_Conversion(void);//ֽ�����޺���

/***********************�Ե�Դ��ѹ�ļ��ȡһ��ʱ���ƽ��ֵ***********************************************/ 

unsigned char SPI2_ReadWriteByte(unsigned char TxData);//SPI2�ڷ��ͺͽ��պ���

void StartSprint(void);//������ӡ������

void SprintLin(void);//��ӡһ��16������;�������ڵĵ����ַ��Ѿ�������

void Sprint_Char(unsigned char *Buffer,unsigned int Count);//��ӡ�ַ�

void OneHotStep(void);//����һ��
 
void Send_OneHalfChar(unsigned int OneHalfChar);// ����һ�����ַ�����ӡͷ�Ļ�����

void Sprint_OneHalfHang(unsigned char *P_Hdata);//��ӡһ�����ݣ�����һ�����ݵĻ�����

void Step_by_Step(void);//һ��һ�����ߣ�һ��Ϊһ�еĵ�Ŀ�� 

#endif


