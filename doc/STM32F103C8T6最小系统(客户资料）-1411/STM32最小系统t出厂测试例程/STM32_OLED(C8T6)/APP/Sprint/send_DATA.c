 /******************************************************************************************
        ;;�ļ�����: send_DATA.c
        ;;�ļ�����: ���ݷ��ͺ���
        ;;��    ��: 
        ;;��д����: 2010��9��23��
        ;;�� �� ��: V1.0
        ;;�����¼:
******************************************************************************************/

 
 
 #include "send_DATA.H"

  
 void DATA_send (unsigned char *DATA_P,unsigned int nCount) 
 {
  
     unsigned int i;
    
	 for(i=0;i<nCount;i++)//��������ת������
         {
            
			 
			 /* Check if the transmit data register is full or not */
            
		    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //��鷢�ͼĴ����Ƿ�Ϊ��
			 
			USART_SendData(USART1, *DATA_P);
			*DATA_P++;
			
         }
             
 
 }
 
 /**********************************��ʼ��������Ϊ0x0����0xFF**********************************/ 
 
void Init_Buffer (unsigned char *P,unsigned int Count,unsigned char Type) 

{
  unsigned int i;
  
   if(Type==0)
   {
   
     for(i=0;i<Count;i++)*P++=0x0;
   
   }
   else
   {
     for(i=0;i<Count;i++)*P++=0xFF;

   }

}



/**************************************************************************************
  �������ܣ��ڴ濽������

**************************************************************************************/
void Copy_Mem (unsigned char *P1, const unsigned char *P2,unsigned int Count)
{
   
   unsigned int i ;
   for(i=0;i<Count;i++)*P1++=*P2++;

  
}


/**************************************************************************************
  �������ܣ��ڴ濽������

**************************************************************************************/
void Copy_Char (unsigned char *P1, unsigned char *P2,unsigned int Count)
{
   
   unsigned int i ;
   for(i=0;i<Count;i++)*P1++=*P2++;

  
}




/**************************************************************************************
  �������ܣ��ڴ�ȽϺ�������
  �Ƚ�ָ��ָ��������������������Ƿ�һ��
  һ������ֵΪ��  0
  ��һ������ֵΪ��1

***************************************************************************************/
unsigned char Compare_Mem (unsigned char *P1,unsigned char *P2,unsigned int Count)
{
   
   unsigned int i ;
   
   for(i=0;i<Count;i++)
   {
    
     if(*P1==*P2)
     {
       
       P1++;
       
       P2++;
       
     }
     else
     {
       return 1;
            
     }
     
   };
    return 0;
  
}



/*************************************************************************************

  �����ֿ��ļ���ʱ�򣬻ظ���λ������Ļظ�����

**************************************************************************************/


void Send_Start(unsigned char baohao1,unsigned char baohao2)//�ظ���λ��

   {
      
      unsigned char state_buffer[10];      //Ӧ������״̬�Ĵ���

      state_buffer[0]=0x01;
      state_buffer[1]=0x05;
      state_buffer[2]=baohao1;
      state_buffer[3]=baohao2;                    
      AH_CRC_Verify (state_buffer,state_buffer[1]-1, 1 );
	    DATA_send (state_buffer,state_buffer[1]+1); 

    }








 

