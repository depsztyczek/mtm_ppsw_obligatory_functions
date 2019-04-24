#include <stdio.h>

enum Result {OK, ERROR};
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
	
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	if((pcStr[0]!='0')|(pcStr[1]!='x')|(pcStr[2]==NULL))
		return ERROR;
	*puiValue = 0;
	for(ucCharacterCounter=2;pcStr[ucCharacterCounter]!=NULL;ucCharacterCounter++){
		ucCurrentCharacter=pcStr[ucCharacterCounter];
		if (ucCharacterCounter>6)
			return ERROR;
		*puiValue=*puiValue<<4;
		if(ucCurrentCharacter<='9')
			*puiValue=*puiValue | (ucCurrentCharacter-'0');
		else
			*puiValue=*puiValue | (ucCurrentCharacter-'A'+10);
		}
	return OK;
}

int main(){
	
	enum Result HEX_ERROR, ERROR_TO_SHORT, ERROR_TO_LONG, OK_HEX;
	char pHEX_ERROR[]="A34";
	char pERROR_TO_SHORT[]="0x";
	char pERROR_TO_LONG[]="0x3523543523";
	char pOK_HEX[]="0x3CA";
	unsigned int puiValue;
	
	HEX_ERROR=eHexStringToUInt(pHEX_ERROR, &puiValue);
	ERROR_TO_SHORT=eHexStringToUInt(pERROR_TO_SHORT, &puiValue);
	ERROR_TO_LONG=eHexStringToUInt(pERROR_TO_LONG, &puiValue);
	OK_HEX=eHexStringToUInt(pOK_HEX, &puiValue);
}