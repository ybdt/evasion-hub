#include <Windows.h>
#include "SimpleUserApcWaitTester.h"
#include <stdio.h>

DWORD
WINAPI
AlertableWaitingThread(
	PVOID ThreadArgument
	)
{
	printf("AlertableWaitingThread, going to wait..\n");

	HANDLE EventHandle = CreateEventA(NULL, TRUE, FALSE, NULL);

	LARGE_INTEGER Timeout;
	Timeout.QuadPart = T_RELATIVE(T_SECONDS(1000));

	DriverWaitForEvent(EventHandle, TRUE, Timeout);

	printf("Exited wait!");
	return 0;
}


VOID
UserApcToAlertableWaitingThread(
	VOID
	)
{
	HANDLE ThreadHandle = CreateThread(
		NULL,
		0,
		AlertableWaitingThread,
		NULL,
		0,
		NULL
	);

	if (ThreadHandle == NULL) {
		printf("CreateThread Failed: 0x%08X\n", GetLastError());
		exit(-1);
	}

	SetThreadPriority(ThreadHandle, THREAD_PRIORITY_TIME_CRITICAL);

	Sleep(2000);

	if (!QueueUserAPC(MyCustomApc, ThreadHandle, 0)) {
		printf("QueueUserAPC Error: 0x%08X\n", GetLastError());
	}

	WaitForSingleObject(ThreadHandle, INFINITE);
}