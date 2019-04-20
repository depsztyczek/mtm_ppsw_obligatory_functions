#include <stdio.h>

void CopyString(char pcSource[], char pcDestination[]){

	unsigned char ucCharacterCounter;

	for(ucCharacterCounter=0; pcSource[ucCharacterCounter]!=NULL;ucCharacterCounter++){
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}		
	pcDestination[ucCharacterCounter]=NULL;
}

