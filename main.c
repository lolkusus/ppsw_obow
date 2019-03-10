#include <LPC21xx.H>

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucLoopCounter;
	for(ucLoopCounter=0;pcSource[ucLoopCounter]!='\0';ucLoopCounter++)
	{
		pcDestination[ucLoopCounter] = pcSource[ucLoopCounter];
	}
	pcDestination[ucLoopCounter] = '\0';
}

int main()
{
	char psSource[] = "Tekst testowy";
	char psDestination[16];
	CopyString(psSource, psDestination);
}
