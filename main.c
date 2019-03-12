#include <LPC21xx.H>

#define HEX_bm 0x000F
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

unsigned char ucTokerNr;

typedef enum CompResult 
{ DIFFERENT , EQUAL } CompResult;

typedef enum Result 
{ OK, ERROR } Result;

typedef enum TokenType 
{KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode 
{ LD, ST, RST} KeywordCode;

typedef union TokenValue
{
enum KeywordCode eKeyword;
unsigned int uiNumber;
char *pcString; 
} TokenValue;

typedef struct Token
{
enum TokenType eType; 
union TokenValue uValue; 
} Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
enum KeywordCode eCode;
char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]= 
{
{RST,"reset"},
{LD, "load" },
{ST, "store"}
};

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcSource[ucLoopCounter]!='\0';ucLoopCounter++)
	{
		pcDestination[ucLoopCounter] = pcSource[ucLoopCounter];
	}
	pcDestination[ucLoopCounter] = '\0';
}

int iTestOf_CopyString()
{
	unsigned char ucLoopCounter;
	char pcTestSource[] = "Test 1";
	char pcTestDest[7];
	//Test 1 sprawdza czy funkcja dobrze kopiuje stringi
	CopyString(pcTestSource,pcTestDest);
	for(ucLoopCounter=0;ucLoopCounter<8;ucLoopCounter++)
	{
		if (pcTestDest[ucLoopCounter] != pcTestSource[ucLoopCounter]) return 1;
	}
	return 0;
}

CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcStr1[ucLoopCounter] != '\0';ucLoopCounter++)
	{
		if (pcStr1[ucLoopCounter] != pcStr2[ucLoopCounter]) return DIFFERENT;
	}
	return EQUAL;
}

int iTestOf_eCompareString()
{
	char pcTest1[] = "Test 1";
	char pcTest2[] = "Tescik 2";
	//Test 2 sprawdza czy funkcja dobrze porownuje stringi
	if (eCompareString(pcTest1,pcTest1) == DIFFERENT) return 1;
	if (eCompareString(pcTest1,pcTest2) == EQUAL) return 1;
	return 0;
}
void AppendString (char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcDestinationStr[ucLoopCounter]!='\0';ucLoopCounter++) {}
	CopyString(pcSourceStr,pcDestinationStr+ucLoopCounter);
}

int iTestOf_AppendString()
{
	char pcTestDest[] = "Test";
	char pcTestSource[] = " 3";
	char pcTestWynik[] = "Test 3";
	//Test 3 sprawdza czy funkcja dobrze dopisuje stringi
	AppendString(pcTestSource,pcTestDest);
	if (eCompareString(pcTestDest,pcTestWynik) == DIFFERENT) return 1;
	return 0;
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar)
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcString[ucLoopCounter]!='\0';ucLoopCounter++)
	{
		if(pcString[ucLoopCounter] == cOldChar) pcString[ucLoopCounter] = cNewChar;
	}
}

int iTestOf_ReplaceCharactersInString()
{
	char pcTestString[] = "Testowy String";
	char pcTestWynik[] = "Tesxowy String";
	//Test 4 sprawdza czy funkcja dobrze zamienia znaki
	ReplaceCharactersInString(pcTestString,'t','x');
	if (eCompareString(pcTestString,pcTestWynik) == DIFFERENT) return 1;
	return 0;
}

void UIntToHexStr(unsigned int uiValue, char pcStr[])
{
	unsigned char ucLoopCounter;
	unsigned char ucCurrentQuad;
	pcStr[0] = '0';
	pcStr[1] = 'x';
	for(ucLoopCounter=0;ucLoopCounter<4;ucLoopCounter++)
	{
		ucCurrentQuad = ((uiValue >> ucLoopCounter*4) & HEX_bm);
		if(ucCurrentQuad>9) pcStr[5-ucLoopCounter] = ucCurrentQuad - 10 + 'A';
		else pcStr[5-ucLoopCounter] = ucCurrentQuad + '0';
	}
	pcStr[6] = '\0';
}

int iTestOf_UIntToHexStr()
{
	char pcString[7];
	char pcTestString[7] = "0xAF19";
	//Test 5 sprawdza czy funkcja dobrze zamienia na hex
	UIntToHexStr(0xAF19,pcString);
	if (eCompareString(pcString,pcTestString) == DIFFERENT) return 1;
	return 0;
}

Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
	unsigned char ucLoopCounter;
	if(pcStr[0] != '0') return ERROR;
	if(pcStr[1] != 'x') return ERROR;
	if(pcStr[2] == '\0') return ERROR;
	*puiValue = 0;
	for(ucLoopCounter=2;ucLoopCounter<7;ucLoopCounter++)
	{
		if(pcStr[ucLoopCounter] == '\0') return OK;
	  *puiValue = *puiValue << 4;
		if(pcStr[ucLoopCounter] >= 'A') *puiValue = *puiValue | (pcStr[ucLoopCounter] - 'A' + 10); 
		else *puiValue = *puiValue | (pcStr[ucLoopCounter] - '0');
	}
	return OK;
}

int iTestOf_eHexStringToUInt()
{
	char liczba[] = "0xAB12";
	unsigned int uiResult;
	//Test 6 sprawdza czy funkcja dobrze zamienia hex na uint
	eHexStringToUInt(liczba,&uiResult);
	if (uiResult != 0xAB12) return 1;
	return 0;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcDestinationStr[ucLoopCounter]!='\0';ucLoopCounter++) {}
	pcDestinationStr[7] = 'g';
	UIntToHexStr(uiValue,pcDestinationStr+ucLoopCounter);
}

int iTestOf_AppendUIntToString()
{
	unsigned int uiNumber = 0xAB12;
	char pcString[14] = "Test 7 ";
	char pcTestString[13] = "Test 7 0xAB12";
	//Test 7 sprawdza czy funkcja dobrze dopisuje string (z hexa) na koniec stringa
	AppendUIntToString(uiNumber,pcString);
	if (eCompareString(pcString,pcTestString) == DIFFERENT) return 1;
	return 0;
}

unsigned char ucFindTokensInString(char *pcString)
{
	unsigned char ucLoopCounter;
	unsigned char ucDelimiterCounter;
	char cCurrentChar;
	enum State {TOKEN, DELIMITER};
	enum State eState = DELIMITER;
	ucDelimiterCounter = 0;
	
	for(ucLoopCounter=0;;ucLoopCounter++)
	{
		cCurrentChar = pcString[ucLoopCounter];
		switch(eState)
		{
			case DELIMITER:
				if(cCurrentChar == '\0') return ucDelimiterCounter;
				else if(cCurrentChar == ' ') {}
				else 
				{
					eState = TOKEN;
					asToken[ucDelimiterCounter].uValue.pcString = pcString+ucLoopCounter;
					ucDelimiterCounter++;
				}
				break;
			case TOKEN:
				if(cCurrentChar == '\0') return ucDelimiterCounter;
				else if(ucDelimiterCounter == MAX_TOKEN_NR) return ucDelimiterCounter;
				else if(cCurrentChar != ' ') {}
				else eState = DELIMITER;
				break;
		}
	}
}

int iTestOf_ucFindTokensInString()
{
	char test1[] = "            ";
	char test2[] = "Token1 Token2";
	char test3[] = "Token1     Token2";
	unsigned char wynik;
	
	wynik = ucFindTokensInString(test1);
	if (wynik != 0) return 1;
	if (asToken[0].uValue.pcString != '\0') return 1;
	
	wynik = ucFindTokensInString(test2);
	if (wynik != 2) return 1;

	wynik = ucFindTokensInString(test3);
	if (wynik != 2) return 1;
	
	return 0;
}

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode)
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;ucLoopCounter<3;ucLoopCounter++)
	{
		if (eCompareString(pcStr,asKeywordList[ucLoopCounter].cString) == EQUAL) 
		{
			*peKeywordCode = asKeywordList[ucLoopCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

int iTestOf_eStringToKeyword()
{
	char cTest[] = "load ";
	enum Result eResult;
	enum KeywordCode eKeywordCode;
	ReplaceCharactersInString(cTest,' ','\0');
	eResult = eStringToKeyword(cTest,&eKeywordCode);
	if (eKeywordCode != LD) return 1;
	else return 0;
}

void DecodeTokens()
{
	unsigned char ucLoopCounter;
	Token* tValue;
	for(ucLoopCounter=0;ucLoopCounter<MAX_TOKEN_NR;ucLoopCounter++)
	{
		tValue = &asToken[ucLoopCounter];
		if (eStringToKeyword(tValue->uValue.pcString,&tValue->uValue.eKeyword) == OK) tValue->eType = KEYWORD;
		else if (eHexStringToUInt(tValue->uValue.pcString,&tValue->uValue.uiNumber) == OK) tValue->eType = NUMBER;
		else tValue->eType = STRING;
	}
}

int iTestOf_DecodeTokens()
{
	char cTest[] = "load   0x1CD2 ala ";
	unsigned char ucTokenCount;
	Token* tValue;
	ucTokenCount = ucFindTokensInString(cTest);
	ReplaceCharactersInString(cTest,' ','\0');
	DecodeTokens();
	
	tValue = &asToken[0];
	if (tValue->eType != KEYWORD) return 1;
	else if (tValue->uValue.eKeyword != LD) return 1;
	tValue = &asToken[1];
	if (tValue->eType != NUMBER) return 1;
	else if (tValue->uValue.uiNumber != 0x1CD2) return 1;
	tValue = &asToken[2];
	if (tValue->eType != STRING) return 1;
	else if (eCompareString("ala",tValue->uValue.pcString) == DIFFERENT) return 1;
	return 0;
}

void DecodeMsg(char *pcString)
{
	unsigned char ucTokenCount;
	ucTokenCount = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ','\0');
	DecodeTokens();
}


int main()
{
	int wynik = iTestOf_DecodeTokens();
}
