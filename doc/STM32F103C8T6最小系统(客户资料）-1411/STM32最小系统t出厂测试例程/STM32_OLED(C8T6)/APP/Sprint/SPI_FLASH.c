
/*************************************************************************

SPI��������

//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25X16
//����Ϊ2M�ֽ�,����32��Block,512��Sector



*************************************************************************/

#include "SPI_FLASH.H"



/*************************************************
�������ܣ�Ӳ��SPI�ڷ��ͻ��߽���һ���ֽ�����

*************************************************/

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
unsigned char SPIx_ReadWriteByte(unsigned char TxData)
{		
	unsigned int retry=0;				 
	while((SPI1->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>2000)return 0;
	}			  
	SPI1->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>2000)return 0;
	}	  						    
	return SPI1->DR;          //�����յ�������				    
}


//��ȡSPI_FLASH��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
unsigned char SPI_Flash_ReadSR(void)   
{  
	unsigned char byte=0;   
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPIx_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     
	return byte;   
} 
//дSPI_FLASH״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void SPI_FLASH_Write_SR(unsigned char sr)   
{   
	SPI_FLASH_CS_LOW();                            //ʹ������   
	SPIx_ReadWriteByte(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	SPIx_ReadWriteByte(sr);               //д��һ���ֽ�  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
}   
//SPI_FLASHдʹ��	
//��WEL��λ   
void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_LOW();                            //ʹ������   
    SPIx_ReadWriteByte(W25X_WriteEnable);      //����дʹ��  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
} 
//SPI_FLASHд��ֹ	
//��WEL����  
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS_LOW();                            //ʹ������   
    SPIx_ReadWriteByte(W25X_WriteDisable);     //����д��ָֹ��    
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
} 			    
//��ȡоƬID W25X16��ID:0XEF14
unsigned short int SPI_Flash_ReadID(void)
{
	unsigned short int Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	SPIx_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_HIGH();				    
	return Temp;
} 

unsigned int  SPI_Flash_ReadDeviceID(void)  	    //��ȡFLASH ID

{
	unsigned int Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	SPIx_ReadWriteByte(0x9F);//���Ͷ�ȡID����	    
	//SPIx_ReadWriteByte(0x00); 	    
	//SPIx_ReadWriteByte(0x00); 	    
	//SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<16;  
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_HIGH();
					    
	return Temp;
} 

  		    
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void SPI_Flash_Read(unsigned char* pBuffer,unsigned int ReadAddr,unsigned short int NumByteToRead)//��ȡSPI FLASH ��ָ����ַ��ʼ��ȡָ�����ȵ�����   
{ 
 	unsigned short int i;    												    
	SPI_FLASH_CS_LOW();                            			//ʹ������   
    SPIx_ReadWriteByte(W25X_ReadData);         				//���Ͷ�ȡ����   
    SPIx_ReadWriteByte((unsigned char)((ReadAddr)>>16));    //����24bit��ַ    
    SPIx_ReadWriteByte((unsigned char)((ReadAddr)>>8));   
    SPIx_ReadWriteByte((unsigned char)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPIx_ReadWriteByte(0XFF);   				//ѭ������  
    }
	SPI_FLASH_CS_HIGH();                            		//ȡ��Ƭѡ     	      
}  
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void SPI_Flash_Write_Page(unsigned char* pBuffer,unsigned int WriteAddr,unsigned short int NumByteToWrite)//SPI��һҳ(0~65535)��д������256���ֽڵ�����
{
 	unsigned short int i;  
    SPI_FLASH_Write_Enable();                  					//SET WEL 
	SPI_FLASH_CS_LOW();                            				//ʹ������   
    SPIx_ReadWriteByte(W25X_PageProgram);      					//����дҳ����   
    SPIx_ReadWriteByte((unsigned char)((WriteAddr)>>16)); 		//����24bit��ַ    
    SPIx_ReadWriteByte((unsigned char)((WriteAddr)>>8));   
    SPIx_ReadWriteByte((unsigned char)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPIx_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	SPI_FLASH_CS_HIGH();                            			//ȡ��Ƭѡ 
	SPI_Flash_Wait_Busy();					   					//�ȴ�д�����
} 
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void SPI_Flash_Write_NoCheck(unsigned char* pBuffer,unsigned int WriteAddr,unsigned short int NumByteToWrite)   
{ 			 		 
	unsigned short int pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)  		   

unsigned char SPI_FLASH_BUF[4096];

void SPI_Flash_Write(unsigned char* pBuffer,unsigned int WriteAddr,unsigned short int NumByteToWrite)   
{ 
	unsigned int secpos;
	unsigned short int secoff;
	unsigned short int secremain;	   
 	unsigned short int i;    
	


	secpos=WriteAddr/4096;//������ַ 0~511 for w25x16
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   

	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			SPI_Flash_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//д����������  

		}else SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	 	 
}
//��������оƬ
//��Ƭ����ʱ��:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//�ȴ�ʱ�䳬��...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                        //ʹ������   
    SPIx_ReadWriteByte(W25X_ChipErase);        //����Ƭ��������  
	SPI_FLASH_CS_HIGH();                       //ȡ��Ƭѡ     	      
	SPI_Flash_Wait_Busy();   				   //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ������������ʱ��:150ms
void SPI_Flash_Erase_Sector(unsigned int Dst_Addr)   
{   
	Dst_Addr*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                            //ʹ������   
    SPIx_ReadWriteByte(W25X_SectorErase);      //������������ָ�� 
    SPIx_ReadWriteByte((unsigned char)((Dst_Addr)>>16));  //����24bit��ַ    
    SPIx_ReadWriteByte((unsigned char)((Dst_Addr)>>8));   
    SPIx_ReadWriteByte((unsigned char)Dst_Addr);  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
    SPI_Flash_Wait_Busy();   				   //�ȴ��������
}  
//�ȴ�����
void SPI_Flash_Wait_Busy(void)   
{   
	
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���

}

  
//�������ģʽ
void SPI_Flash_PowerDown(void)   
{ 
  	SPI_FLASH_CS_LOW();                            //ʹ������   
    SPIx_ReadWriteByte(W25X_PowerDown);        //���͵�������  
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
    delay_ms(1);                               //�ȴ�TPD  
}   
//����
void SPI_Flash_WAKEUP(void)   
{  
  	SPI_FLASH_CS_LOW();                            //ʹ������   
    SPIx_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS_HIGH();                            //ȡ��Ƭѡ     	      
    delay_ms(1);                               //�ȴ�TRES1
}   


//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//2010/5/27
static unsigned int TimingDelay;

void SysTick_init(void)
{

	SysTick_Config(SystemFrequency / 1000);

}								    

 /**
  * @brief  Inserts a delay time.
  * @param nTime: specifies the delay time length, in milliseconds.
  * @retval : None
  */
void delay_ms(unsigned int nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval : None
  */



void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}



extern unsigned  int 	  ID;

extern unsigned char TxBuffer[10];//���ڷ��ͻ�����
extern unsigned char RxBuffer[1000]; //���ڽ��ջ�����

//�벻Ҫ���ú������ú�������ʹ��ӡ�����ֿ��𻵵����޷���ӡ���ַ�























