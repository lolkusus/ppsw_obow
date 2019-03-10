#include <LPC21xx.H>

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

int main()
{
	int wynik = iTestOf_CopyString();
}
