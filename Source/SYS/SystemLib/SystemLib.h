#include "Keyword.h"

PRIVATE U16 CaculateCheckSum(U08* pData, U16 u16DataSize)
{
	    U16 u16Checksum = 0;
	    U16 u16Index = 0;

	    for (u16Index = 0; u16Index < u16DataSize; u16Index++) {
	    	u16Checksum ^= pData[u16Index]; // Thực hiện phép XOR giữa checksum và từng byte dữ liệu
	    }

	    return u16Checksum;
}
