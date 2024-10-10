/******************************************************************************************
        ;;�ļ�����: Sprint.c
        ;;�ļ�����: ��ӡ�������ļ�
        ;;��    ��: 
        ;;��д����: 2009��04��22��
        ;;�� �� ��: V1.0
        ;;�����¼:
******************************************************************************************/
 
#include "Sprint.H"

extern unsigned char SP_DATA[72];//ȡһ���ַ��Ļ�����

unsigned char SprintZF[24][64];//��ӡһ���ַ��ĵ�������


/*************************************************************************
 
         ����һ�����ַ�����ӡͷ�Ļ�����
 
 **************************************************************************/
 
 void Send_OneHalfChar(unsigned int OneHalfChar)

  {
    
    unsigned int i;
    
    unsigned int j;
 
    for(i=0;i<12;i++)
    {
    
      j=OneHalfChar&0x8000;
      
      OneHalfChar=OneHalfChar<<1;
      
      if(j==0x8000)
      {
      
        PR_DIN_SET();

      }
      else
      {
      
        PR_DIN_REST();

      }
       
       
	     PR_CLK_REST();//���ݴ���ʱ�ӵ͵�ƽ��������
 
       PR_CLK_SET();//���ݴ���ʱ�Ӹߵ�ƽ����������
	   
    }
 
  }

 
/**********************����һ�����ֽ�ģʽ�������Ҵ�ӡ***********************************************************/ 
 
 void Sprint_OneHalfHang(unsigned char *P_Hdata)//��ӡһ�����ݣ�����һ�����ݵĻ�����
 {
   
	  unsigned char i;
	  unsigned int  j;
	  unsigned char Half_char[2];
	  
  
	  for(i=0;i<32;i++)
	  {
	    
	    Half_char[0]=*P_Hdata;
	    
	    P_Hdata++;
	    
	    Half_char[1]=*P_Hdata;
	    
	    P_Hdata++;
	  
	    j=(unsigned int )Half_char[0];
	    
	    j=j<<8;
	    
	    j=j+(unsigned int )Half_char[1];
	    
	    Send_OneHalfChar(j);
	  
	  }
	     
  
 }


void Step_Time(void)////�߲���ʱ

 {
   unsigned int i;
   for(i=0;i<MotorDly;i++);
 
 }

/***********************���������������***********************************************/
 
unsigned int Num_Step=0;//��������ߵĲ��� 
 
unsigned char OneStep;//��һ���ı��� 

unsigned char Single_Srep;//��ӡ�����ߵ�һ��
 
void Step_by_Step(void) 
 {
      
     while(Num_Step>0)
        {
                  
        if(Single_Srep==0)
        {
        
         if(OneStep==0) //��������ߵ�һ��
          {
             MOT1_SET();//MOT1=1;	 
        	   MOT2_REST();//MOT2=0;  	
        	   MOT3_SET();//MOT3=0;	
        	   MOT4_REST();//MOT4=1;
        	   OneStep=1;
			       Step_Time();//�߲���ʱ
          }
          else if(OneStep==1) //��������ߵڶ���
          {
             MOT1_SET();//MOT1=1;  
             MOT2_REST();//MOT2=0;  
             MOT3_REST();//MOT3=1;	
             MOT4_SET();//MOT4=0;
             OneStep=0;
             Single_Srep=1;//�л�����
             Num_Step--; //�߲�������.
			       Step_Time();//�߲���ʱ   
          }
          
        }
        else
        {
        
          if(OneStep==0) //��������ߵ�����
          {
             MOT1_REST();//MOT1=0;  
             MOT2_SET();//MOT2=1;   
             MOT3_REST();//MOT3=1;	
             MOT4_SET();//MOT4=0;
             OneStep=1; 
			       Step_Time();//�߲���ʱ 
          }
          else if(OneStep==1) //��������ߵ��Ĳ�
          {
             MOT1_REST();//MOT1=0;	
             MOT2_SET();//MOT2=1;  	
             MOT3_SET();//MOT3=0;	 
             MOT4_REST();//MOT4=1;
             OneStep=0;
             Single_Srep=0;//�л����� 
             Num_Step--; //�߲�������.
			       Step_Time();//�߲���ʱ
			    
          }
         
        }
      
      }
      //else //�������ֹͣ 
      {  
         MOT1_REST();//MOT1=0;  //ֹͣ���������ŵ�״̬
         MOT2_REST();//MOT2=0;
         MOT3_REST();//MOT3=0;
         MOT4_REST();//MOT4=0;

	  }


 }






/*************************************************************************************

����һ����һ������


***************************************************************************************/ 

void Hot_Time(void)//������ʱ

 {
   unsigned int i;
   for(i=0;i<Hotup_Time;i++);
 
 }


//��һ���ļ��ȴ������Ը���ʵ��Ӧ������趨�����磬����ǵ�ع��磬���Է�Ϊ��μ���

 void OneHotStep(void)
 {
 
     
/***************************  �����μ���   **********************************************/

//��һ�μ���        
     
         STB1_SET();//���ȴ�ӡ����
	       STB2_SET();//���ȴ�ӡ����
	       STB3_SET();//���ȴ�ӡ����
	       
	       Hot_Time();//������ʱ
	 
//	       STB2_REST();//���ȴ�ӡ����
//         
//	       STB3_REST();//���ȴ�ӡ����


//�ڶ��μ���       
       
//         STB2_SET();//���ȴ�ӡ����
//	 
//	       STB1_REST();//���ȴ�ӡ����
//         
//	       STB3_REST();//���ȴ�ӡ����

//         Hot_Time();//������ʱ
				 
//�����μ���    
       
//         STB3_SET();//���ȴ�ӡ����
//	 
//	       STB1_REST();//���ȴ�ӡ����
//         
//	       STB2_REST();//���ȴ�ӡ����

//         Hot_Time();//������ʱ
         

//ֹͣ����
       
       
       STB1_REST();//ֹͣ���ȴ�ӡ����
         
       STB2_REST();//ֹͣ���ȴ�ӡ����
       
       STB3_REST();//ֹͣ���ȴ�ӡ����			 
      
     
 /***********************���������������***********************************************/ 
	   
	    Num_Step=1; //�߲�
	   
	    Step_by_Step();



 }




/***********************ֽ�����޺���***********************************************/ 

unsigned char  Paper_Conversion(void)
{
 
 unsigned char ReadValue;

 ReadValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);

 return ReadValue;
  
}




/***********************������ӡ����������***********************************************/ 

extern unsigned char Startup;  //����������ӡ���

extern unsigned char RxBuffer[1000]; //���ڽ��ջ�����

extern unsigned int Num_Sprint;//Ҫ��ӡ�ֽ���λ����ֽ���


void StartSprint(void)
{

  if(Startup==0xff)					//�����⵽����������ɱ�ǣ���������ʼ��ӡ����
  {

		
			__set_PRIMASK(1);//�ر����ж�
		
			USART_ITConfig(USART1, USART_IT_RXNE,DISABLE); //�رս����ж�

			Startup=0;						//���������ӡ���
			
			Sprint_Char(RxBuffer,Num_Sprint);//��ӡ

			Num_Sprint=0;					//��ӡ�����ݺ�����ݽ�������

			USART_ITConfig(USART1, USART_IT_RXNE,ENABLE); //�򿪽����ж�
		
			__set_PRIMASK(0);    //���ж�
		
		
  }

}









/************************************************************************************************************

������:void SprintLin(void)

��ӡһ��16������;�������ڵĵ����ַ��Ѿ�������

																								
************************************************************************************************************/


unsigned int Py=0;    //���������ݵ�ƫ��

unsigned char Lin_DATA[72];//ȡһ���ַ��Ļ�����

unsigned char CharDot[1536];//����Ҫ��ӡһ�����ݵĵ�������

void SprintLin(void)

{


   unsigned char *Pchar;//ָ��
   
   unsigned char Cyc_H=0;//ѭ����ʱ����
   
   unsigned char Cyc_L=0;//ѭ����ʱ����
   
 
  //����Ƿ���ֽ��
         
    
   for(Cyc_L=0;Cyc_L<24;Cyc_L++)
         {

           Pchar=Lin_DATA;//ָ��һ��Ҫ��ӡ���ݵĻ�����
           
           for(Cyc_H=0;Cyc_H<32;Cyc_H++)
           {
              
              Py=(unsigned int)Cyc_H*48+(unsigned int)Cyc_L*2;
              
              *Pchar=CharDot[Py];
              
               Pchar++;
               
              *Pchar=CharDot[Py+1];
              
               Pchar++;
              
           
           }
     
	  
	      
      Sprint_OneHalfHang(Lin_DATA);//�����ӡһ���ַ�
                     
      //Sprint_LA_REST();//����һ�����ݵ���ӡ�Ĵ���
	  
	  Sprint_LA_REST();//����һ�����ݵ���ӡ�Ĵ���
           
      Sprint_LA_SET();//����һ�����ݵ���ӡ�Ĵ���
		   

	  OneHotStep();//����һ�У�������ֽһ��


//��һ�����ݽ����ظ���ӡ�����ڸ߶ȷŴ�һ����
	 

//		Sprint_OneHalfHang(Lin_DATA);//�����ӡһ���ַ�
//                     
//      //Sprint_LA_REST();//����һ�����ݵ���ӡ�Ĵ���
//	  
//	  Sprint_LA_REST();//����һ�����ݵ���ӡ�Ĵ���
//           
//      Sprint_LA_SET();//����һ�����ݵ���ӡ�Ĵ���
//		   

//	  OneHotStep();//����һ�У�������ֽһ��

	   } 

        

}           





/**************************************************************************************
       
�������ܣ���ӡ���ݴ������ 1

          �����յ������ݽ���;���ҽ����ݴ�ӡ

���������unsigned int Count��Ҫ������ַ�����

����ֵ �����ص�һ�в������ַ�����

**************************************************************************************/ 


unsigned char QW[2];//��λ����ʱ���û�����

unsigned int Half_Char[2];//����ַ��Ļ�����

unsigned int Buffer_PY=0;//��ȡ��λ�뻺������ַƫ��

unsigned int LNum=0;//���󻺳�������

unsigned char SpintHalf[72];//��ӡ���ֽڴ�����ʱ������

unsigned char Lin=32;//һ���д�ӡ���ַ�����

 
void Sprint_Char(unsigned char *Buffer,unsigned int Count)
 
 {
    
    unsigned char Half;//ȡ���ַ��ı��
    
    unsigned char Half_Cyc;//���ַ�����ѭ��
    
    unsigned char *P1_Half;//���ַ�����ָ��
    
    unsigned char *P2_Half;//���ַ�����ָ��

	Buffer_PY=0;//��ӡ�ַ��ӻ������ڶ����ֽڿ�ʼ����һ���ֽ�Ϊ������

	LNum=0;     //���󻺳�������

	Lin=32;	   //һ���д�ӡ���ַ�����


	while(Count>0)
	{
	
	 Copy_Mem(QW,&RxBuffer[Buffer_PY],2);//�ӻ�������ȡ�����ֽڵ���λ��
    
	 Buffer_PY++; //ת����һ��Ҫ������λ���λ��

     if((QW[0]==0x0D)|(QW[0]==0x0A))//�жϵ�ǰҪ������ַ��Ƿ�Ϊ�س�����
      {
        
        Count--;  //ת�Ƶ���һ��Ҫ�жϵ���λ����Ҫ�жϵ������ֽڵ���λ��
        
        if((QW[1]==0x0D)|(QW[1]==0x0A))
        {
        
        
          Buffer_PY++;
          
          Count--;  //ת�Ƶ���һ��Ҫ�жϵ���λ����Ҫ�жϵ������ֽڵ���λ��
        
        }

	 while(Lin>0) //�ж�һ��֮���Ƿ������ݿ�������Ҫ���
        {
          
         Lin--;//ֱ��һ�����ݴ洢���
          
         Init_Buffer(SP_DATA,48,0);//���ַ��Ļ���������0;
           
         Copy_Char(&CharDot[LNum],SP_DATA,48);//�����ݿ�������ӡ���󻺳���

         LNum=LNum+48;//ת����һ��Ҫд�������
        
         if(LNum==1536) //���װ���˻�����;
          
          {
            
            LNum=0;
              
           SprintLin();//������ӡ����������

            if( NO_Paper==Paper_Conversion())//�ж��Ƿ���ֽ����ֽ���˳���ӡ
               {
                     
                  Startup=0;//�����ӡ��� 
    
                  Count=0;//��ӡ��ɣ������ӡ���

                  return;
                     
                }
              
            }
            
            
          }
        
        if(LNum!=0)
        {
          
          
          SprintLin();//������ӡ����������
          
          if( NO_Paper==Paper_Conversion())//�ж��Ƿ���ֽ����ֽ���˳���ӡ
               {
                     
                  Startup=0;//�����ӡ��� 
    
                  Count=0;//��ӡ��ɣ������ӡ���

                  return;
                     
                }
        
        }
        
        LNum=0;        //�����仺����ָ��
        
        Lin=32;
      
      }
	  
     
 
 /*******************  ������ǻس����ţ���ȫ���ַ������ȡ�ַ�����  *****************************************/      
	        
      else if(QW[0]&0x80)//�ж��Ƿ�Ϊһ���ַ�ȫ��
       {
          if(QW[1]&0x80) 
          {
            
            Buffer_PY++;
                        
            for(Half=0;Half<2;Half++)//�����һ���ַ��Ļ���һ��ȡ����ַ�
            {
              
              Char_Addr(QW[0],QW[1]);//�������Ϊ���ֵ���λ����
             
			  Copy_Mem(SpintHalf,SP_DATA,72); //��ȡ�����ַ����õ�һ����ʱ��������
              
              P1_Half=SpintHalf;
              
              P2_Half=SP_DATA;
              
              for(Half_Cyc=0;Half_Cyc<24;Half_Cyc++)
              {
               if(Half==0)
               {
                
                   *P2_Half=*P1_Half;
                    P2_Half++;
                    P1_Half++;
                   *P2_Half=*P1_Half;
                   P2_Half++;
                   P1_Half++;
                   P1_Half++;
                 
               }
               else
               {
                 P1_Half++;
                 
                 Half_Char[0]=(unsigned int )*P1_Half;
                 
                 Half_Char[0]=Half_Char[0]<<12;
                 
                 P1_Half++;
                 
                 Half_Char[1]=*P1_Half;
                 
                 P1_Half++;
                 
                 Half_Char[1]=(unsigned int )Half_Char[1]<<4;
                 
                 Half_Char[0]=Half_Char[0]+Half_Char[1];
                 
                 *P2_Half=(unsigned char)(Half_Char[0]>>8);
                 
                  P2_Half++;
                  
                 *P2_Half=(unsigned char)Half_Char[0]&0xff;
                 
                  P2_Half++;
                  
               }
              }
              
			  
			  Copy_Char(&CharDot[LNum],SP_DATA,48);//�����ݿ�������ӡ���󻺳���
              
              LNum=LNum+48;//ת����һ��Ҫд�������
              
              if(LNum==1536) //���װ���˵��󻺳�������������ӡ;
              
              {
              	SprintLin();//������ӡ����������
				LNum=0;
                
              }
              
              
              Lin--;  //�����24�ĵ����ֿ⣬��һ�еĺ��ָ���Ϊ16��
              
              if(Lin==0)
              {
                
                Lin=32;//��ֹ���
                
              }
             
			  Count--;  //ת�Ƶ���һ��Ҫ�жϵ���λ����Ҫ�жϵ������ֽڵ���λ��
            
              }
              
			}
        
        
	        else //��ʾASC��չ�ַ�
	        {
	           
	           
	           
	              ASC_Addr(QW[0]);//ȡASCII���ַ���
	           
	              
				  Copy_Mem(&CharDot[LNum],SP_DATA,48);//�����ݿ�������Ҫд��Flash�Ļ�����
				                
	              LNum=LNum+48;//ת����һ��Ҫд�������
	              
	              if(LNum==1536) //���װ���˵��󻺳�������������ӡ;
	              
	              {
	                  
	                  SprintLin();//������ӡ����������
	                  LNum=0;                 
	              
	              }
	              
	              
	              Lin--;  //�����24�ĵ����ֿ⣬��һ�еĺ��ָ���Ϊ16��
	              
	              if(Lin==0)
	              {
	              
	                
	                Lin=32;//��ֹ���
	                
	              }
	              
	              Count=Count-1;  //ת�Ƶ���һ��Ҫ�жϵ���λ����Ҫ�жϵ������ֽڵ���λ��
	
	       	   }
	        
		}

		else   //����������ֽ��ַ�����ȡASC��ĵ����ַ�
		{

		 
              ASC_Addr(QW[0]);//ȡASCII���ַ���
           
              Copy_Mem(&CharDot[LNum],SP_DATA,48);//�����ݿ�������Ҫд��Flash�Ļ�����
              
              LNum=LNum+48;//ת����һ��Ҫд�������
              
              if(LNum==1536) //���װ���˵��󻺳�������������ӡ;
              
              {
              
                  SprintLin();//������ӡ����������
              	  LNum=0;
              }
              
              
              Lin--;  //�����24�ĵ����ֿ⣬��һ�еĺ��ָ���Ϊ16��
              
              if(Lin==0)
              {
              
                
                Lin=32;//��ֹ���
                
              }
              
              Count=Count-1;  //ת�Ƶ���һ��Ҫ�жϵ���λ����Ҫ�жϵ������ֽڵ���λ��


		}
     
      }

    if(Lin<32)//������һ�в����Իس���β�ģ������һ��ʣ����ֽ�������������ҽ��洢ҳ����1
     {
         
	   while(Lin>0) //�ж�һ��֮���Ƿ������ݿ�������Ҫ���
        {
          
         Lin--;//ֱ��һ�����ݴ洢���
          
         Init_Buffer(SP_DATA,48,0);//���ַ��Ļ���������0;
           
         Copy_Char(&CharDot[LNum],SP_DATA,48);//�����ݿ�������ӡ���󻺳���

         LNum=LNum+48;//ת����һ��Ҫд�������
        
         if(LNum==1536) //���װ���˻���������дһ��Flash;
          
          {
            
            LNum=0;
              
           SprintLin();//������ӡ����������

            if( NO_Paper==Paper_Conversion())//�ж��Ƿ���ֽ����ֽ���˳���ӡ
               {
                     
                  Startup=0;//�����ӡ��� 
    
                  Count=0;//��ӡ��ɣ������ӡ���

                  return;
                     
                }
              
            }
            
          }
        
        if(LNum!=0)
        {
          
          
          SprintLin();//������ӡ����������
          
          if( NO_Paper==Paper_Conversion())//�ж��Ƿ���ֽ����ֽ���˳���ӡ
               {
                     
                  Startup=0;//�����ӡ��� 
    
                  Count=0;//��ӡ��ɣ������ӡ���

                  return;
                     
                }
        
        }
        
        LNum=0;        //�����仺����ָ��
        
        Lin=32;
         
         }

  }
     

