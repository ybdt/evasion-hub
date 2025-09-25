#include <Windows.h>
#include <stdio.h>
#include <winternl.h>

typedef
VOID
(*PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3,
	PVOID ContextRecord
	);

typedef NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD)(
	IN HANDLE ThreadHandle,
	IN PPS_APC_ROUTINE ApcRoutine,
	IN PVOID SystemArgument1 OPTIONAL,
	IN PVOID SystemArgument2 OPTIONAL,
	IN PVOID SystemArgument3 OPTIONAL
	);

VOID
PrintApcPreviousRIP(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3,
	PCONTEXT ContextRecord
);

PNT_QUEUE_APC_THREAD NtQueueApcThread;

int 
main(
	int argc,
	const char** argv
	)
{
	NtQueueApcThread = (PNT_QUEUE_APC_THREAD)(GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueueApcThread"));
	
	NtQueueApcThread(
		GetCurrentThread(),
		PrintApcPreviousRIP,
		NULL,
		NULL,
		NULL
	);

	SleepEx(0, TRUE);

	return 0;
}


VOID
PrintApcPreviousRIP(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3,
	PCONTEXT ContextRecord
	)
{
	printf("RIP = 0x%08I64X\n", (ULONG_PTR)ContextRecord->Rip);
}