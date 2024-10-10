
 /**********************************************************************************************
 
    ��ӡ�ӿڵ����ó�ʼ���ļ�


 
 
 
 
 **********************************************************************************************/



#ifndef __Sprint_Config_H
#define __Sprint_Config_H 1


#include "stm32f10x.h"//����ͷ�ļ�



#define  LED0_ON()   GPIO_ResetBits(GPIOC, GPIO_Pin_13) 

#define  LED0_OFF()  GPIO_SetBits(GPIOC, GPIO_Pin_13) //LED�ߵ�ƽ��


//#define  LED1_ON()   GPIO_ResetBits(GPIOD, GPIO_Pin_2) 

//#define  LED1_OFF()  GPIO_SetBits(GPIOD, GPIO_Pin_2) //LED�ߵ�ƽ��


void SysTick_init(void);

void delay_ms(unsigned int nTime);

void TimingDelay_Decrement(void);


void GPIO_Configuration(void);// ϵͳʹ�õ�IO�ڳ�ʼ�� 

void RCC_Configuration(void); // ʱ�ӷ����ʼ��

void NVIC_Configuration(void);//�ж����ȼ������ʼ��

void USART_Configuration(void); //���ڳ�ʼ������

void TIM2_Config(void);			//��ʱ����ʼ��

void SPI1_Init(void);           //Ӳ��SPI1�ڳ�ʼ��

void SPI2_Init(void);           //Ӳ��SPI2�ڳ�ʼ��

unsigned char SPI1_ReadWriteByte(unsigned char TxData);//SPI1���ջ��߷���һ������

unsigned char SPI2_ReadWriteByte(unsigned char TxData);//SPI2���ջ��߷���һ������

#endif
