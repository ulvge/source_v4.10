/**
  ******************************************************************************
  * @file    Project/Template/main.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main program body
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
#include "stm32f10x.h"

unsigned char *P_RXD;//��������ָ��

unsigned int Num_RXD=0;//Ҫ��ӡ�ֽ���λ����ֽ���


unsigned char TxBuffer[64]={0,2,3,};//���ڷ��ͻ�����

unsigned char RxBuffer[64]; //���ڽ��ջ�����

unsigned char Key0=0;

unsigned char Key0_Value=0;

unsigned char Key0_State=0;

unsigned char LED0_State=0;

unsigned char t;

unsigned char JG;//���ݱȽϽ��


void Key_Delay (void)
{
	unsigned int i;
	
	for(i=0;i<0xfff;i++);
	
	
}




void Time_Delay (void)
{
	unsigned int i;
		unsigned int j;
	
	for(i=0;i<0xfff;i++)
	{
		
		for(j=0;j<0xFFFF;j++);
  };
	
	
}





/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

 

/* Private function prototypes -----------------------------------------------*/

//void Delay(int nCount);


/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  SystemInit();

  RCC_Configuration();

  NVIC_Configuration();

  GPIO_Configuration();

  SysTick_init();		     //��ʱ��ʼ��

  SPI2_Init(); 			     //��ʼ��SPIӲ����

	P_RXD=RxBuffer;//����ָ��ָ����ջ�����
	
  USART_Configuration();  //USART1���� 

  TIM2_Config();			//��ʱ����ʼ�� 
	


 
    OLED_Init();			 //��ʼ��OLED      
  	OLED_ShowString(1,0, "0.96' OLED TEST");  
  	OLED_ShowString(1,16,"mcudev.taobao  ");  
   	OLED_ShowString(1,32,"2014-06-16");  
  	OLED_ShowString(1,48,"ASCII: ");  
  	OLED_ShowString(63,48,"CODE: "); 

		{
			unsigned char i;
			
			for(i=0;i<32;i++)TxBuffer[i]=i;
			
    }
		
		I2CWriteByte(0,TxBuffer,32); //д�볤��
			
		I2CReadByte(0,RxBuffer,32);
			
		JG=Compare_Mem (TxBuffer,RxBuffer,32);
		
		if(JG==0)//��Eeprom���ж�д�ж�;
		{
			OLED_ShowString(1,32,"Eeprom--OK  ");
			}
		else
			{
				OLED_ShowString(1,32,"Eeprom--Error  ");
      }

 
  /* Infinite loop */
  while (1)
  {
		
		OLED_ShowChar(48,48,t,16,1);// OLED_Refresh_Gram();
		
		t++;
		if(t>'~')t=' ';
		
		OLED_ShowNum(103,48,t,3,16);//
		
    
		if(Key0_State==0xff)
		{
      LED0_State=!LED0_State;
			 delay_ms(300);
			Key0_State=0;
     
      }
		
		if(LED0_State==0)
				 {
					 LED0_ON();//LED��
					 delay_ms(200);
					 LED0_OFF();//LED��
					 delay_ms(200); 
			 }
		
  }

}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {


   

  }
}
#endif



/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
