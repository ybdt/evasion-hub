#include <Windows.h>
#include <stdio.h>

VOID
NTAPI
ApcCode1(
	ULONG_PTR dwData
	)
{
	printf("Hello from ApcCode1\n");
}

VOID 
NTAPI
ApcCode2(
	ULONG_PTR dwData
	)
{
	printf("Hello from ApcCode2\n");
}


int main(
	int argc,
	const char** argv
	)
{
	printf("Queueing APCs..\n");

	QueueUserAPC(ApcCode1, GetCurrentThread(), 0);
	QueueUserAPC(ApcCode2, GetCurrentThread(), 0);
		
	printf("Entering alertable state..\n");

	SleepEx(0, TRUE);

	printf("Exiting..\n");
}