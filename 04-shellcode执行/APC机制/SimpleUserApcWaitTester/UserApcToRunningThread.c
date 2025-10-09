#include <Windows.h>
#include "SimpleUserApcWaitTester.h"


DWORD
NonAlertableThread(
	PVOID ThreadArgument
)
{
	LARGE_INTEGER Timeout;

	printf("NonAlertableThread, sleeping (non-alertable)..\n");

	HANDLE EventHandle = CreateEventA(NULL, TRUE, FALSE, NULL);

	//
	// Sleep for 10 seconds.
	//
	Sleep(10*1000);

	printf("Entering alertable state!\n");
	
	Timeout.QuadPart = T_RELATIVE(T_SECONDS(1000));

	DriverWaitForEvent(EventHandle, TRUE, Timeout);

	return 0;
}


VOID
UserApcToNonAlertableThread(
	VOID
)
{
	HANDLE ThreadHandle = CreateThread(
		NULL,
		0,
		NonAlertableThread,
		NULL,
		0,
		NULL
	);

	if (ThreadHandle == NULL) {
		printf("CreateThread Failed: 0x%08X\n", GetLastError());
		exit(-1);
	}

	Sleep(2000);

	if (!QueueUserAPC(MyCustomApc, ThreadHandle, 0)) {
		printf("QueueUserAPC Error: 0x%08X\n", GetLastError());
	}

	WaitForSingleObject(ThreadHandle, INFINITE);
}