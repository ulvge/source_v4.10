#ifndef   __CRC_H
#define   __CRC_H    1

#include "stdio.h"

/*
**************************************************************************************************************
*										    ��  ��
**************************************************************************************************************
*/
 extern  unsigned short int  AH_CRC_Verify( unsigned char  *str, unsigned short int size, unsigned char mode ); /* У�����ݵ�CRC      */
 extern  unsigned int  AH_Full_0F_Verify( unsigned char  *str, unsigned int  size );              /* ȫ0ȫFУ��         */
 extern  unsigned char  CRC_CHECK ( unsigned char *strFrame, unsigned char crc_longth );        /*  */                                                                              

#endif
//���ݽṹ����

