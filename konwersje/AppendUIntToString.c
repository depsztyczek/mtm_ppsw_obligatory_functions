#include<stdio.h>
#define HEX_bm 0xF

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
	
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;
	
	pcStr[0]='0';
	pcStr[1]='x';
	for(ucNibbleCounter=0;ucNibbleCounter<4;ucNibbleCounter++){
		ucCurrentNibble=((uiValue >> ucNibbleCounter*4) & HEX_bm);
		if(ucCurrentNibble>9)
			pcStr[5-ucNibbleCounter] = ucCurrentNibble - 10 + 'A';
		else
			pcStr[5-ucNibbleCounter] = ucCurrentNibble + '0';
	}
	pcStr[6]=NULL;
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){

	unsigned char ucEndPointer;
	
	for(ucEndPointer=0;pcDestinationStr[ucEndPointer]!=NULL;ucEndPointer++){}
	UIntToHexStr(uiValue, pcDestinationStr + ucEndPointer);
}