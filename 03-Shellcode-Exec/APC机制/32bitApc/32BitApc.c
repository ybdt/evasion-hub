#include <windows.h>
#include <stdio.h>

VOID 
WINAPI
ApcCode(
	ULONG_PTR dwData
	)
{
	printf("32 bit code!\n");
}

int main()
{
	QueueUserAPC(ApcCode, GetCurrentThread(), 0);

	SleepEx(INFINITE, TRUE);
}