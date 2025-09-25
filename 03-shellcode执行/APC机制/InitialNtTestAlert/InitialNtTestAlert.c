#include <Windows.h>
#include <stdio.h>
#include <winternl.h>


VOID
WINAPI
ApcRoutine(
	ULONG_PTR dwData
	);


DWORD
WINAPI
NewThread(
	PVOID ThreadArgument
	);

int
main(
	int argc,
	const char** argv
)
{
	HANDLE ThreadHandle = CreateThread(
								NULL,
								0,
								NewThread,
								NULL,
								CREATE_SUSPENDED,
								NULL
							);
		
	
	if (!QueueUserAPC(
		ApcRoutine,
		ThreadHandle,
		0
	)) {
		printf("Error queueing APC\n");
	}	

	printf("APC Queued. Calling ResumeThread..\n");

	ResumeThread(ThreadHandle);

	WaitForSingleObject(ThreadHandle, INFINITE);

	return 0;
}

VOID
WINAPI
ApcRoutine(
	ULONG_PTR dwData
)
{
	printf("Inside the ApcRoutine.\n");
}


DWORD
WINAPI
NewThread(
	PVOID ThreadArgument
	)
{
	printf("Inside the thread.\n");
	return 0;
}
