#include <stdio.h>

enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[]){

	unsigned char ucCharacterCounter;

	for(ucCharacterCounter=0; pcStr1[ucCharacterCounter]!=NULL; ucCharacterCounter++){
		if (pcStr1[ucCharacterCounter]!=pcStr2[ucCharacterCounter]){
			return DIFFERENT;
		}
	}
	return EQUAL;
}

