
#ifndef  _TM1637_DRV_H
#define  _TM1637_DRV_H

#ifndef  GLOBALS_TM1637_DRV
	#define  TM1637_DRV_EXT	extern
#else
	#define  TM1637_DRV_EXT  
#endif

#include	"typedef.h"




//���ŵ�ʱ��ʹ�ܺ����ĺ궨��
#define TM1637_RCC_Cmd    RCC_APB2PeriphClockCmd
//DIO��CLK������ŵĺ궨�壬�û�ֻ��Ҫ�޸���غ꼴��
#define    TM_DIO_PORT    	GPIOB		                 
#define    TM_DIO_CLK 	    RCC_APB2Periph_GPIOB		
#define    TM_DIO_PIN		GPIO_Pin_15			        

#define    TM_CLK_PORT    	GPIOB			              
#define    TM_CLK_CLK 	    RCC_APB2Periph_GPIOB		
#define    TM_CLK_PIN		GPIO_Pin_13			

//ʱ���ߺ������߸ߵ͵�ƽ�ĺ궨�壬�����޸�
#define      CLK_1         GPIO_SetBits(TM_CLK_PORT,TM_CLK_PIN)
#define      CLK_0         GPIO_ResetBits(TM_CLK_PORT,TM_CLK_PIN)
#define      DIO_1         GPIO_SetBits(TM_DIO_PORT,TM_DIO_PIN)
#define      DIO_0         GPIO_ResetBits(TM_DIO_PORT,TM_DIO_PIN)

typedef struct {
	char shi;
	char ge;
}DispHour, DispMin;

typedef struct {
	DispHour hour;
	DispMin min;
}DispContext;

typedef enum {
	DISPLAY_TYPE_TIME,
	DISPLAY_TYPE_TEMPERATURE,
	DISPLAY_TYPE_FREQUENCY,
}TM1637_DISPLAY_TYPE;

typedef struct {
	TM1637_DISPLAY_TYPE type;
	INT32U lastTimeRefreshCycle;
	DispContext context;
}DispPara;

//��غ�������  
TM1637_DRV_EXT void TM1637_GPIOInit(void);
TM1637_DRV_EXT void I2C_Start(void);
TM1637_DRV_EXT void I2C_stop(void);
TM1637_DRV_EXT void TM1637_WriteBit(unsigned char mBit);
TM1637_DRV_EXT void TM1637_WriteByte(unsigned char Byte);
TM1637_DRV_EXT void TM1637_WriteCommand(unsigned char mData);
TM1637_DRV_EXT void TM1637_WriteData(unsigned char addr, unsigned char mData);
TM1637_DRV_EXT void TM1637_DisplayVal(TM1637_DISPLAY_TYPE type, INT32U val, INT32U dlyMs);
#endif

