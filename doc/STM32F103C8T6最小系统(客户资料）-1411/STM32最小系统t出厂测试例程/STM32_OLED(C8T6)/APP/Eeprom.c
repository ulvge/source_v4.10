                                         
#include "Eeprom.h"

#include "stm32f10x.h"//����ͷ�ļ�


/****************************************************************************

                                          ģ��IIC����

**************************************************************************/

	void SDA_Out(void)
	
	{
	  
//	  	 	  GPIOB->CRL&=0X0FFFFFFF;
//	          GPIOB->CRL|=0X80000000;
	  
	  
	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	          //��ʼ��SDA
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  //�������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	}


    void SDA_In(void)

	{

//	  GPIOB->CRL&=0X0FFFFFFF;
	 // GPIOB->CRL|=0X80000000;

	   GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	          //��ʼ��SDA
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  //��������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	}





const unsigned char cucBit2[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void DelayIntr2(unsigned char Time_CLK)
	{
	  
	  unsigned short Time;
	  while(Time_CLK--)
	  {
	     for(Time=0;Time<50;Time++)__NOP();
	   } 
	    	
	}

void I2cStart2(void)
{
	
	SDA_Out();
	
	SET_SDA2();
	SET_SCL2();
	DelayIntr2(4);
	CLR_SDA2();							
	DelayIntr2(4);
	CLR_SCL2();		
}

void I2cStop2(void)
{
	SDA_Out();
	CLR_SCL2();
    CLR_SDA2(); 
    DelayIntr2(4);
	SET_SCL2();
	DelayIntr2(4);
	SET_SDA2();	
}


unsigned char WaitAck2(void)
{
	unsigned long ucErrTime2 = 0xfffff;	
	
	unsigned char SDA_Indata;
		
	   SDA_In();//DDRM_DDRM4=0;  //���ݽ��շ����л�----����
	          
	   SET_SDA2();

       DelayIntr2(1);

	   SET_SCL2();

	   DelayIntr2(1);

	   SDA_Indata=READ_SDA2(); 
	         
       while(SDA_Indata==1)
         {
             SDA_Indata=READ_SDA2();
			 DelayIntr2(1);
			 ucErrTime2--; 

             if (ucErrTime2 == 0) 
                 {
					 I2cStop2();
                     return (1);

                 }
          }


       CLR_SCL2();
       return (0);
}

void SendAck2(void)
{
	CLR_SCL2();

	SDA_Out();

    CLR_SDA2();

	DelayIntr2(2);

	SET_SCL2();

  	DelayIntr2(2);

  	CLR_SCL2();	
}

void SendNotAck2(void)
{
	CLR_SCL2(); 

	SDA_Out();

    SET_SDA2();

  	DelayIntr2(2);

 	SET_SCL2();

  	DelayIntr2(2);

  	CLR_SCL2();	
}


void I2cSend2(unsigned char ucData2)
{
	unsigned char IIC_i;

	SDA_Out();//����Ϊ���

	CLR_SCL2();

	for (IIC_i=0;IIC_i<8;IIC_i++)
	{
		
	
		if ( (ucData2 & cucBit2[IIC_i]) != 0)
		      {
		       	SET_SDA2();
	       	}
		else
		      {
		        CLR_SDA2();
		      }


		DelayIntr2(2);

		SET_SCL2();

		DelayIntr2(2);
		
		CLR_SCL2();

		DelayIntr2(2);
		
				
	};

}

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK  
unsigned char I2cReceive2(unsigned char ACK)
{
	unsigned char ucData2 = 0x00;
	unsigned char IIC_i;
	
	SDA_In();

	SET_SDA2();

	for (IIC_i=0;IIC_i<8;IIC_i++)
	{
			
		CLR_SCL2();
		DelayIntr2(2);
		SET_SCL2();
		//SDA_In();//DDRM_DDRM4=0;	 //���ݽ��շ����л�----����
		
		if (READ_SDA2())
		{
			ucData2 |= cucBit2[IIC_i];
		}
		DelayIntr2(1);
				  
	};
	
	if(!ACK)
	{
	    SendNotAck2();
	}
	else SendAck2();//����Ӧ��
	//SDA_Out();//DDRM_DDRM4=1;	   //���ݽ��շ����л�----����
	
	
	return ucData2;
}


/****************************************************************************
I2Cд����
uchar chip_addr��������ַ
uchar mem_addr�� �����ڲ��洢����ַ
uchar *buf��     д�����ݱ���Ļ�������ַ
uchar count��    д�����ݳ���
****************************************************************************/
unsigned char I2CWriteByte(unsigned int mem_addr,unsigned char*DDATAp,unsigned int count)
{ 
 
  unsigned int E2_i;
 
  unsigned int Timer_1ms;
  
  unsigned char Addr1;
  
  unsigned char Addr2;
  
  unsigned char Addr3;

  unsigned char SDA_REdata;
  

  for(E2_i=0;E2_i<count;E2_i++)
    {    
        
      Addr3=(unsigned char)(mem_addr/256);
           
      Addr3=Addr3<<1;
           
      Addr1=0xa0|Addr3;
           
      Addr2=(unsigned char)mem_addr%256;    
       
        I2cStart2();
        
        I2cSend2(Addr1);//���͵�ַ
        
        Timer_1ms=60000;

       SDA_REdata=WaitAck2(); 
	      
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
        
       I2cSend2(Addr2);//���͵�ַ
        
        Timer_1ms=60000;     
        
       SDA_REdata=WaitAck2();  
	     
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
        
        
          I2cSend2(*DDATAp);
          Timer_1ms=60000;     
           SDA_REdata=WaitAck2();    
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
          
        I2cStop2();
        
        Timer_1ms=0xFFFF;
        
        while(Timer_1ms--)
		{
			__NOP();
	
		}
          
        DDATAp++;
        
        mem_addr++;
    };
   
  return(0);     // write over return 0

}



/*********************************************
I2C������
uchar chip_addr��������ַ
uchar mem_addr�� �����ڲ��洢����ַ
uchar *buf��     �������ݱ���Ļ�������ַ
uchar count��    �������ݳ���
*********************************************/


unsigned char I2CReadByte(unsigned int mem_addr,unsigned char *DATAp,unsigned int count)
{ 
  unsigned int E2_i;
  
  unsigned int Timer_1ms; 
  
  unsigned char Addr1;
  
  unsigned char Addr2;
  
  unsigned char Addr3;

  unsigned char SDA_REdata;
  
  Addr3=(unsigned char)(mem_addr/256);
       
  Addr3=Addr3<<1;
       
  Addr1=0xa0|Addr3;
       
  Addr2=(unsigned char)mem_addr%256;   
  
  
  I2cStart2();
  
  I2cSend2(Addr1);
  
  Timer_1ms=60000;    
  
  SDA_REdata=WaitAck2();    
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
  
 
  I2cSend2(Addr2);
  
  Timer_1ms=60000;     
  
  SDA_REdata=WaitAck2();    
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
   
   
  I2cStart2();
  
  I2cSend2(Addr1+1); 
  
  
  Timer_1ms=60000;     
   SDA_REdata=WaitAck2();    
       while (SDA_REdata)
        {
          
		  SDA_REdata=WaitAck2(); 

		  Timer_1ms--;
          if(Timer_1ms==0)
          {      
             
             return(1); 
          } ;
        };
   
    
  for(E2_i=0;E2_i<count-1;)
  { 
   
    *DATAp= I2cReceive2(1);  // read IIC datawhile       
    
    //SendAck2();
    
    DATAp++;
    E2_i++;
    
    
  }

  *DATAp= I2cReceive2(0);  // read IIC datawhile 
          
  //SendNotAck2();
    
  I2cStop2();// STOP bit;//����ֹͣ�ź�
    
  E2_i=9000;
    
  while(E2_i--);
 
  return(0);
  
  
}




   
  








