/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */


extern unsigned char *P_RXD;//��������ָ��

extern unsigned int Num_RXD;//Ҫ��ӡ�ֽ���λ����ֽ���

extern unsigned char RxBuffer[256]; //���ڽ��ջ�����

extern unsigned char Key0;
extern unsigned char Key0_Value;
extern unsigned char Key0_State;


extern unsigned char Key1;
extern unsigned char Key1_Value;
extern unsigned char Key1_State;

extern unsigned char WK_up_Key;
extern unsigned char WK_up_Key_Value;
extern unsigned char WK_up_Key_State;


extern unsigned char LED0_State;
extern unsigned char LED1_State;


unsigned int Time_delay=0;

void SysTick_Handler(void)	 //һ����ϵͳ�ж�
{
  
  
  TimingDelay_Decrement();
  
	
			//��ȡ�������µİ���ֵ
		

   	Key0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	
	  if(Key0==0)
			{
				if(Key0_Value<100)
					{
            Key0_Value++;
           }
					 else
						 {
							 Key0_State=0xff;//���ð������±��
							 Key0_Value=0;
               }
				
       }
	
		

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/




 




/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval : None
  */
/**********************************************************************
* ��    �ƣ�USART1_IRQHandler()
* ��    �ܣ�USART1�ж�
* ��ڲ�����
* ���ڲ�����
* ȫ�ֱ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/

 



void USART1_IRQHandler(void)
{

  if(1== GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
  {
  	 LED0_ON();
  }
  else
  {
  	 LED0_OFF();
  };

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	 //���ָ����USART�жϷ������
  {
    
	*P_RXD=USART_ReceiveData(USART1); //��ȡ���ջ��������ݡ�    /* Read one byte from the receive data register */
	 P_RXD++;
	 Num_RXD++;

	 if(Num_RXD>=255)	//��ֹ�������
	 {
	 	Num_RXD=0;
		P_RXD=RxBuffer;//ָ��������ݻ�����
		
	}
  }
 

}


 /*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

uint16_t capture = 0;

extern __IO uint16_t CCR1_Val;

extern __IO uint16_t CCR2_Val;


void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) //���ָ����TIM�жϷ������
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);//���TIMx���жϴ�����λ

    /* Pin PC.06 toggling with frequency = 73.24 Hz */
    //GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));
    capture = TIM_GetCapture1(TIM2); //���TIMx���벶��1��ֵ
    TIM_SetCompare1(TIM2, capture + CCR1_Val);//����TIMx����Ƚ�1�Ĵ���ֵ

	
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

    /* Pin PC.07 toggling with frequency = 109.8 Hz */
    //GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
    capture = TIM_GetCapture2(TIM2);
    TIM_SetCompare2(TIM2, capture + CCR2_Val);
  }
  
  capture = TIM_GetCounter(TIM2);
 
  TIM_SetCounter(TIM2, 0);


}



/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
