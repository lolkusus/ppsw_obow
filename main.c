#include <LPC21xx.H>

typedef enum CompResult 
{ DIFFERENT , EQUAL } CompResult;

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcSource[ucLoopCounter]!='\0';ucLoopCounter++)
	{
		pcDestination[ucLoopCounter] = pcSource[ucLoopCounter];
	}
	pcDestination[ucLoopCounter+1] = '\0';
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
	for(ucLoopCounter=0;ucLoopCounter<8;ucLoopCounter++)
	{
		if (pcStr1[ucLoopCounter] != pcStr2[ucLoopCounter]) return DIFFERENT;
	}
	return EQUAL;
}

int iTestOf_eCompareString()
{
	char pcTest1[] = "Test 1";
	char pcTest2[] = "Tescik 2";
	
	if (eCompareString(pcTest1,pcTest1) == DIFFERENT) return 1;
	if (eCompareString(pcTest1,pcTest2) == EQUAL) return 1;
	return 0;
}

int main()
{
	int wynik = iTestOf_eCompareString();
}
