

/*********************************************************************************

 
SPI��������ͷ�ļ�







**********************************************************************************/





#ifndef   __SPI_FLASH_H 
#define   __SPI_FLASH_H     1

#include "stm32f10x.h"//����ͷ�ļ�

/*********************************************************************** 
   SPI���Ŷ���
 
    MOSI  ---        
 
    MISO  ---        
 
    SCLK  ---        
 
     CS  ---         
 
************************************************************************/



/* Select SPI FLASH: Chip Select pin low  */
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
/* Deselect SPI FLASH: Chip Select pin high */
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

//W25X16��д
#define FLASH_ID 0XEF14
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void SysTick_init(void);
void delay_ms(unsigned int nTime);
void TimingDelay_Decrement(void);


void SPI_Flash_Init(void);
unsigned short int  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
unsigned int  SPI_Flash_ReadDeviceID(void);  	    //��ȡFLASH ID

unsigned char	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void SPI_FLASH_Write_SR(unsigned char sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Enable(void);  //дʹ�� 
void SPI_FLASH_Write_Disable(void);	//д����

void SPI_Flash_Write_Page(unsigned char* pBuffer,unsigned int WriteAddr,unsigned short int NumByteToWrite);//SPI��һҳ(0~65535)��д������256���ֽڵ�����

void SPI_Flash_Read(unsigned char* pBuffer,unsigned int ReadAddr,unsigned short int NumByteToRead);   //��ȡflash
void SPI_Flash_Write(unsigned char* pBuffer,unsigned int WriteAddr,unsigned short int NumByteToWrite);//д��flash
void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_Flash_Erase_Sector(unsigned int Dst_Addr);//��������
void SPI_Flash_Wait_Busy(void);           //�ȴ�����
void SPI_Flash_PowerDown(void);           //�������ģʽ
void SPI_Flash_WAKEUP(void);			  //����

void TestFlash (void);//����Flash

#endif

