
 /**********************************************************************************************
 
    ��ӡ�ӿڵ����ó�ʼ���ļ�


 
 
 
 
 **********************************************************************************************/



#ifndef __Sprint_Config_H
#define __Sprint_Config_H 1


#include "stm32f10x.h"//����ͷ�ļ�



#define  SPK_ON()    GPIO_SetBits(GPIOA, GPIO_Pin_8)

#define  SPK_OFF()   GPIO_ResetBits(GPIOA, GPIO_Pin_8)   //�������ߵ�ƽ��



#define  LED1_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_11) 

#define  LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_11) //LED�ߵ�ƽ�����͵�ƽ��


#define  LED2_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_10) 

#define  LED2_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_10) //LED�ߵ�ƽ�����͵�ƽ��


void GPIO_Configuration(void);// ϵͳʹ�õ�IO�ڳ�ʼ�� 
void RCC_Configuration(void); // ʱ�ӷ����ʼ��
void NVIC_Configuration(void);//�ж����ȼ������ʼ��

void ADC_init(void)	 ; 			//����ADת������ʼ��DMAͨ������ת��
void USART_Configuration(void); //���ڳ�ʼ������
void TIM2_Config(void);			//��ʱ����ʼ��
void SPI1_Init(void);           //Ӳ��SPI1�ڳ�ʼ��
void SPI2_Init(void);           //Ӳ��SPI2�ڴ�ӡ����ڳ�ʼ��

void Sprint_init(void);           //Ӳ��SPI2�ڳ�ʼ��


#endif
