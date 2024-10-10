 /**********************************************************************************************
 
      ADת��C�ļ�
 
 
 
 
 **********************************************************************************************/
 
#include "BSP_Config.H"
 
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

extern unsigned short int ADCConvertedValue; //ADת���Ľ��


/*******************************************************************************


							��ʼ��ͨ��IO��


********************************************************************************/

void GPIO_Configuration(void)
{
  
  
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD, ENABLE);

	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PC13��ʼ��LED0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PC13��ʼ��LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

 
//����1�Ͱ���2,����3��IO��ʼ��  �ļ�ֵ���  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
 
	 

/*********************��ʼ������IO����**********************************/

 /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


}
 


/*******************************************************************************


	ʹ�ܻ���ʧ��AHB����ʱ��


********************************************************************************/


void RCC_Configuration(void)
{
  
/* Enable peripheral clocks --------------------------------------------------*/
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable  clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  	//ʹ�ܴ���1��ʱ��

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//ʹ�ܶ�ʱ��2��ʱ��
 
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
  //                      RCC_APB2Periph_GPIOC , DISABLE);  


}


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval : None
  */

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�������ȼ����飺��ռ���ȼ��ʹ����ȼ�
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


    /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
  
}








 void ADC_init(void)
 {
  DMA_InitTypeDef DMA_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;


  /* DMA channel1 configuration ----------------------------------------------*/
 
 //��DMA��ͨ��x�Ĵ�������Ϊȱʡֵ
  DMA_DeInit(DMA1_Channel1);

//�ò������Զ���DMA�������ַ

  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;

//�ò������Զ���DMA�ڴ����ַ

  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADCConvertedValue;

//DMA_DIR�涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ

  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

//DMA_BufferSize���Զ���ָ��DMAͨ����DMA����Ĵ�С

  DMA_InitStructure.DMA_BufferSize = 1;

//DMA_PeripheralInc�����趨�����ַ�Ĵ����������

  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

//DMA_MemoryInc�����趨�ڴ��ַ�Ĵ����������

  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;

 //DMA_PeripheralDataSize�趨���������ݿ��

  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

//DMA_MemoryDataSize�趨���ڴ����ݿ��

  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

//DMA_Mode������ѭ������ģʽ

  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

//DMA_Priority�趨DMAͨ��x��������ȼ� :DMAͨ��xӵ�������ȼ�

  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

//DMA_M2Mʹ��DMAͨ�����ڴ浽�ڴ洫��

  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

//��DMA_InitStruct�е�ÿһ��������ȱʡֵ����

  DMA_Init(DMA1_Channel1, &DMA_InitStructure);


  
  /* Enable DMA channel1 */

 //ʹ�ܻ���ʧ��ָ����ͨ��x

  DMA_Cmd(DMA1_Channel1, ENABLE);
     
  /* ADC1 configuration ------------------------------------------------------*/

 //ADC1��ADC2�����ڶ���ģʽ
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;


 //ADC_ScanConvMode�涨��ģ��ת��������ɨ��ģʽ����ͨ�������ǵ��Σ���ͨ����ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;


//ADC_ContinuousConvMode�涨��ģ��ת���������������ǵ���ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;


//ADC_ExternalTrigConv������ʹ���ⲿ��������������ͨ����ģ��ת��
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;


//ADC_DataAlign�涨��ADC��������߶��뻹�����ұ߶���
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

//ADC_NbreOfChannel �涨��˳����й���ת����ADCͨ������Ŀ

  ADC_InitStructure.ADC_NbrOfChannel = 1;

//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel10 configuration */ 

//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��

  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */

//ʹ�ܻ���ʧ��ָ����ADC��DMA����

  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */

 //ʹ�ܻ���ʧ��ָ����ADC

  ADC_Cmd(ADC1, ENABLE);



  /* Enable ADC1 reset calibaration register */ 
  
//����ָ����ADC��У׼�Ĵ���  
    
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */

//��ȡADC����У׼�Ĵ�����״̬

  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */


//��ʼָ��ADC��У׼״̬

  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */

//��ȡָ��ADC��У׼����

  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 

//ʹ�ܻ���ʧ��ָ����ADC�����ת����������

  ADC_SoftwareStartConvCmd(ADC1, ENABLE);



 }


/**********************************************************************
* ��    �ƣ�USART_Configuration()
* ��    �ܣ���������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵�������ڳ�ʼ������
***********************************************************************/
 void USART_Configuration(void)                        
{


/* USART1 and USART1 configuration ------------------------------------------------------*/
  /* USART and USART1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  USART_InitTypeDef USART_InitStructure;
  //USART_ClockInitTypeDef  USART_InitClock;						//���崮�ڳ�ʼ��ʱ�ӽṹ��

  USART_InitStructure.USART_BaudRate = 9600;//9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  //USART_InitClock.USART_Clock = USART_Clock_Disable; 				//����ʱ�ӽ�ֹ
  //USART_InitClock.USART_CPOL = USART_CPOL_Low; 					    //ʱ���½�����Ч
  //USART_InitClock.USART_CPHA = USART_CPHA_2Edge;					//�����ڵڶ���ʱ���ز�׽
  //USART_InitClock.USART_LastBit = USART_LastBit_Disable;			//�������λ��ʱ�����岻�����SCLK����
																	
  //USART_ClockInit(USART1,&USART_InitClock);//��ʼ��USART1��Χʱ�ӣ����� USART_ClockInitStruct �ڵĲ���.

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);

  /* Enable USART1 Receive and Transmit interrupts */
  USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
  //USART_ITConfig(USART1, USART_IT_TC,DISABLE);

  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);


}







unsigned short int CCR1_Val = 49152;	//0xC000
unsigned short int CCR2_Val = 32768;	//0x8000
//unsigned short int CCR3_Val = 16384;	//0x4000
//unsigned short int CCR4_Val = 8192;	//0x2000


/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval : None
  */
void TIM2_Config(void)
{


	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;


 /* ---------------------------------------------------------------
    TIM2 Configuration: Output Compare Timing Mode:
    TIM2CLK = 36 MHz, Prescaler = 4, TIM2 counter clock = 7.2 MHz
    CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz
    CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 Hz
    CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4 Hz
    CC4 update rate = TIM2 counter clock / CCR4_Val =  878.9 Hz
  --------------------------------------------------------------- */

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535;//TIM_Period����������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler = 0;//TIM_Prescaler������������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //TIM_ClockDivision������ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM2, 4, TIM_PSCReloadMode_Immediate);//����TIMxԤ��Ƶ:TIMԤ��Ƶֵ��ʱװ��

  /* Output Compare Timing Mode configuration: Channel1 */
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; //TIM����Ƚ�ʱ��ģʽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//TIM_Pulse�����˴�װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM����Ƚϼ��Ը�

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel3 */
 // TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 // TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

 // TIM_OC3Init(TIM2, &TIM_OCInitStructure);

 // TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel4 */
 // TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

 // TIM_OC4Init(TIM2, &TIM_OCInitStructure);

 // TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);//ʹ�ܻ���ʧ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���

  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 , ENABLE);
  //TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);//ʹ�ܻ���ʧ��TIMx����


}

/*******************************************************************************
* Function Name  : HW_SPI_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   
  /* Enable SPI1 and GPIOA clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
  
  /* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PA.4 as Output push-pull, used as Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //����Ϊ��SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //ʱ�����ո�
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//���ݲ����ڵڶ���ʱ����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	//�ڲ�NSS�ź���SSIλ����
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//������Ԥ��ƵֵΪ4
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7; //SPI_CRCPolynomial����������CRCֵ����Ķ���ʽ
  SPI_Init(SPI1, &SPI_InitStructure);
  
  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);

  SPI_FLASH_CS_LOW();
  
  
     
}


void SPI2_Init(void)           //Ӳ��SPI2�ڳ�ʼ��

{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   
  /* Enable SPI2 and GPIOB clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE) ;//ʹ��SPI2��ʱ��
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��IO��ʱ��
  
  /* Configure SPI2 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure PB.12 as Output push-pull, used as Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, GPIO_Pin_12);//���ô�ӡͷ�������Ƭѡ�ź�Ϊ��
  
  /* Deselect the Sprint: Chip Select high */
  //SPI_Sprint_CS_HIGH();

  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //����Ϊ��SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //ʱ�����ո�
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//���ݲ����ڵڶ���ʱ����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	//�ڲ�NSS�ź���SSIλ����
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//������Ԥ��ƵֵΪ2
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7; //SPI_CRCPolynomial����������CRCֵ����Ķ���ʽ
  SPI_Init(SPI2, &SPI_InitStructure);
  
  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);

  //SPI_Sprint_CS_LOW();
    
}


 
void Sprint_init(void)           //Ӳ��SPI2�ڳ�ʼ��

{
 
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��IO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ��IO��ʱ��

  //��ʼ��STB1��STB2��STB3��LAT��PR_CLK��PR_DIN

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;//�����PB12��PB15��PB13������ΪIO������ݵ���ӡͷ�ķ�ʽ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //��ʼ��MOT1��MOT2��MOT3��MOT4��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

 
//��ʼ�������¶ȼ������TM ����ʼ����ȱֽ�������EP_T
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�������룬��Ϊ�ⲿ�Ѿ�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
    
  //SPI2_Init();           //Ӳ��SPI2�ڳ�ʼ��	����ʼ�������������ӡͷ��SPI2��


}











