#include <Windows.h>
#include <stdio.h>

typedef
VOID
(*PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

typedef
NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD)(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);


PNT_QUEUE_APC_THREAD NtQueueApcThread;

VOID ApcCode(ULONG_PTR dwData)
{
	printf("ApcCode.\n");
}

int main()
{
	NtQueueApcThread = (PNT_QUEUE_APC_THREAD)GetProcAddress(GetModuleHandle("ntdll"), "NtQueueApcThread");

	QueueUserAPC(ApcCode, GetCurrentThread(), 0);

	NtQueueApcThread(GetCurrentThread(), NULL, NULL, NULL, NULL);
}