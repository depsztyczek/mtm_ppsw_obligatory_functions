#include <stdio.h>

void ReplaceCharactersInString(char pcString[], char cOldCharacter, char cNewChar){

	unsigned char ucCharacterCounter;

	for(ucCharacterCounter=0; pcString[ucCharacterCounter]!=NULL; ucCharacterCounter++){
		if (pcString[ucCharacterCounter]== cOldCharacter){ 
			pcString[ucCharacterCounter]=cNewChar;
		}
	}
}
