#ifndef   __send_DATA_H
#define   __send_DATA_H     1

/******************************************************************
�����ļ�
*****************************************************************/
#include "stm32f10x.h"//����ͷ�ļ�

/********************************************************************

   
    DATA_P:Ҫ���з��͵����ݵ��׵�ַ
    nCount:Ҫ���з��͵����ݵĳ���

 *******************************************************************/

void DATA_send (unsigned char *DATA_P,unsigned int nCount);

void Init_Buffer (unsigned char *P,unsigned int Count,unsigned char Type);//��ʼ��������Ϊ0x0����0xFF

void Copy_Mem (unsigned char *P1,const unsigned char *P2,unsigned int Count);//�������ܣ��ڴ濽������


void Copy_Char (unsigned char *P1, unsigned char *P2,unsigned int Count);//�������ܣ����ֽ��ڴ濽������

unsigned char Compare_Mem (unsigned char *P1,unsigned char *P2,unsigned int Count);//�������ܣ��ڴ�ȽϺ�������

void Send_Start(unsigned char baohao1,unsigned char baohao2);//�ظ���λ��


#endif 

