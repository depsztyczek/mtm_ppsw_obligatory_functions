#include <LPC21xx.H>
#include <stdio.h>

#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

typedef enum Result 
{OK, ERROR} Result;

typedef enum TokenType 
{KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode 
{LD, ST, RST} KeywordCode;

typedef union TokenValue{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char *pcString; 
} TokenValue;

typedef struct Token{
	enum TokenType eType; 
	union TokenValue uValue; 
} Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]= 
{
	{RST,"reset"},
	{LD, "load" },
	{ST, "store"}
};

unsigned char ucTokenNumber=3;
//-----------------------------------------------------------------------
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


void ReplaceCharactersInString(char pcString[], char cOldCharacter, char cNewChar){

	unsigned char ucCharacterCounter;

	for(ucCharacterCounter=0; pcString[ucCharacterCounter]!=NULL; ucCharacterCounter++){
		if (pcString[ucCharacterCounter]== cOldCharacter){ 
			pcString[ucCharacterCounter]=cNewChar;
		}
	}
}
//-----------------------------------------------------------------------
unsigned char ucFindTokensInString(char *pcString){
	
	unsigned char ucTokenPointer;
	unsigned char ucTokenCounter;
	char cCurrentChar;
	enum State {TOKEN, DELIMITER};
	enum State eState = DELIMITER;
	ucTokenCounter = 0;
	
	for(ucTokenPointer=0;;ucTokenPointer++){
		cCurrentChar = pcString[ucTokenPointer];
		switch(eState){
			case DELIMITER:
				if(cCurrentChar == NULL) 
					return ucTokenCounter;
				else if(cCurrentChar == ' ') {}
				else {
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = pcString+ucTokenPointer;
					ucTokenCounter++;
				}
				break;
			case TOKEN:
				if(cCurrentChar == NULL) 
					return ucTokenCounter;
				else if(ucTokenCounter == MAX_TOKEN_NR) 
					return ucTokenCounter;
				else if(cCurrentChar != ' ') {}
				else 
					eState = DELIMITER;
				break;
		}
	}
}


enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode){
	
	unsigned char ucTokenCounter;
	
	for(ucTokenCounter=0;ucTokenCounter<MAX_TOKEN_NR;ucTokenCounter++){
		if (eCompareString(pcStr,asKeywordList[ucTokenCounter].cString) == EQUAL) {
			*peKeywordCode = asKeywordList[ucTokenCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}


void DecodeTokens(){
	
	unsigned char ucTokenCounter;
	Token* tValue;
	
	for(ucTokenCounter=0;ucTokenCounter<ucTokenNumber;ucTokenCounter++){
		tValue = &asToken[ucTokenCounter];
		if (eStringToKeyword(tValue->uValue.pcString,&tValue->uValue.eKeyword) == OK)
			tValue->eType = KEYWORD;
		else if (eHexStringToUInt(tValue->uValue.pcString,&tValue->uValue.uiNumber) == OK) 
			tValue->eType = NUMBER;
		else 
			tValue->eType = STRING;
	}
}


void DecodeMsg(char *pcString){
	ucTokenNumber = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ',NULL);
	DecodeTokens();
}
//-----------------------------------------------------------------------
enum Result eTestOf_ucFindTokensInString()
{
	char test1[] = "            ";
	char test2[] = "Token1 Token2";
	char test3[] = "Token1     Token2";
	unsigned char wynik;
	
	wynik = ucFindTokensInString(test1);
	if (wynik != 0) 
		return ERROR;
	if (asToken[0].uValue.pcString != '\0') 
		return ERROR;
	wynik = ucFindTokensInString(test2);
	if (wynik != 2) 
		return ERROR;
	wynik = ucFindTokensInString(test3);
	if (wynik != 2) 
		return ERROR;
	return OK;
}

enum Result eTestOf_eStringToKeyword()
{
	char cTest[] = "load ";
	enum KeywordCode eKeywordCode;
	ReplaceCharactersInString(cTest,' ','\0');
	eStringToKeyword(cTest,&eKeywordCode);
	if (eKeywordCode != LD) 
		return ERROR;
	else 
		return OK;
}

enum Result eTestOf_DecodeTokens()
{
	char cTest[] = "load   0x1CD2 ala ";
	Token* tValue;
	ucFindTokensInString(cTest);
	ReplaceCharactersInString(cTest,' ','\0');
	DecodeTokens();
	
	tValue = &asToken[0];
	if (tValue->eType != KEYWORD) 
		return ERROR;
	else if (tValue->uValue.eKeyword != LD) 
		return ERROR;
	tValue = &asToken[1];
	if (tValue->eType != NUMBER) 
		return ERROR;
	else if (tValue->uValue.uiNumber != 0x1CD2) 
		return ERROR;
	tValue = &asToken[2];
	if (tValue->eType != STRING) 
		return ERROR;
	else if (eCompareString("ala",tValue->uValue.pcString) == DIFFERENT) 
		return ERROR;
	return OK;
}

int main()
{
    enum Result eReturnValue1, eReturnValue2, eReturnValue3;
    
    eReturnValue1 = eTestOf_ucFindTokensInString();
    eReturnValue2 = eTestOf_eStringToKeyword();
    eReturnValue3 = eTestOf_DecodeTokens();
    
    
    return 0;
}
