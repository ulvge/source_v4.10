#define		GLOBALS_FLASHIAP 
#include	"includes.h"
          
INT32U Flash_getPartitionLength(INT32U partitionID);
INT32U Flash_getPartitionStartAddr(INT32U partitionID);

INT32U ReadFromFlashOneWord(INT32U addr)
{
	//��Flash�ж�ȡһ���֣�����ֵĶ�ȡ��
	INT32U HData, LData;//�����λ����λ��������
	HData = (__IO INT16U)addr;
	LData = (__IO INT16U)(addr + 2);
	return (HData << 16) + LData;
}

INT16U ReadFromFlashHalfWord(INT32U addr)
{
	//��ȡ32λ�ֽ����ݺ󷵻�16λ����
	return (INT16U)(*(( INT32U *)addr));
}

INT32 Flash_ReadFromFlashMass(INT32U partitionID, INT32U offset, INT8U *readData, INT32U readLen)
{
	if ((offset + readLen) > Flash_getPartitionLength(partitionID)) {
		return FAIL;
	}
	INT32U startAddr = Flash_getPartitionStartAddr(partitionID);
	INT16U i;
	for (i = 0; i < readLen / 2; i++) {
		INT16U res = ReadFromFlashHalfWord(startAddr + i*2);
		readData[i*2] = (INT8U)(res&0xFF);
		readData[i*2+1] = (INT8U)(res>>8);
	}
	if ((readLen % 2) == 1) {
		INT16U byte = ReadFromFlashHalfWord(startAddr + i*2);
		readData[i*2] = (INT8U)(byte&0xFF);
	}
	return SUCCESS;
}

FLASH_PARTITION_ID_TABLE g_flashPartitionID[2] = {
	{PARTITION_UID , 0x1FF80050, 12},
	{PARTITION_USER_KEY , PARTITION_USER_KEY_ADDR, PARTITION_USER_KEY_LEN},
};
INT32U Flash_getPartitionLength(INT32U partitionID)
{
	if (partitionID > sizeof(g_flashPartitionID)/ sizeof(FLASH_PARTITION_ID_TABLE)) {
		return 0;
	}
	return g_flashPartitionID[partitionID].len;
}
INT32U Flash_getPartitionStartAddr(INT32U partitionID)
{
	if (partitionID > sizeof(g_flashPartitionID) / sizeof(g_flashPartitionID[0])) {
		return 0;
	}
	return g_flashPartitionID[partitionID].startAddr;
}
#define HALF_WORD_LENGHT_BYTE	2
INT32 Flash_WriteToFlashMass(INT32U partitionID, INT32U offset, INT8U *writeData, INT32U writeLen)
{
	if ((offset + writeLen) > Flash_getPartitionLength(partitionID)) {
		return FAIL;
	}
	INT32U startAddr = Flash_getPartitionStartAddr(partitionID);        
    FLASH_Status flashStatus;
	//��Flashָ���ĵ�ַд��һ����
	FLASH_Unlock();
	//�����־λ
	//FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	//����
	FLASH_ErasePage(startAddr);
	//д��Flash
	INT16U halfWordWriteVal;
	INT32U i = 0;
	for (i = 0; i < (writeLen / 2); i++) {
		halfWordWriteVal = (writeData[i * 2+1]<<8)| writeData[i * 2];
		flashStatus = FLASH_ProgramHalfWord(startAddr + i * HALF_WORD_LENGHT_BYTE, halfWordWriteVal);
		if (flashStatus != FLASH_COMPLETE) {  //FLASH_COMPLETE��ʾ�������  
	        FLASH_Lock();  
			return -1;
		}
	}
	if ((writeLen % 2) == 1) {
		halfWordWriteVal = writeData[writeLen];
		flashStatus = FLASH_ProgramHalfWord(startAddr + i * HALF_WORD_LENGHT_BYTE, halfWordWriteVal);
		if (flashStatus != FLASH_COMPLETE) {  //FLASH_COMPLETE��ʾ�������   
	        FLASH_Lock();  
			return -1;
		}
	}
	//����Flash
	FLASH_Lock();  
	return SUCCESS;
}
//��д���ԣ�
//
//uint32_t TestData = 0x12345678;
//uint32_t TestAddr = 0x0800F000;                 //д��Flash
//WriteToFlashOneWord(TestAddr, TestData);
//HAL_Delay(100);
//
////uint16_t OutData;
//uint8_t HData1, HData2, LData1, LData2;
//
//HData1 = (uint8_t)(TestData >> 24);
//HData2 = (uint8_t)(TestData >> 16);
//LData1 = (uint8_t)(TestData >> 8);
//LData2 = (uint8_t)TestData;
//
////OutData=ReadFromFlashHalfWord(TestAddr);
//Send_Buffer[61] = HData1;
//Send_Buffer[62] = HData2;
//Send_Buffer[63] = LData1;
//Send_Buffer[64] = LData2;
//HAL_UART_Transmit(&hlpuart1, Send_Buffer, 70, 10);


