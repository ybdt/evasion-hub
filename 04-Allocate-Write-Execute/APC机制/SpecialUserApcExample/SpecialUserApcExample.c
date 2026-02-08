#include <Windows.h>
#include <stdio.h>
#include <winternl.h>


typedef
VOID
(*PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

typedef enum _QUEUE_USER_APC_FLAGS {
	QueueUserApcFlagsNone,
	QueueUserApcFlagsSpecialUserApc,
	QueueUserApcFlagsMaxValue
} QUEUE_USER_APC_FLAGS;

typedef union _USER_APC_OPTION {
	ULONG_PTR UserApcFlags;
	HANDLE MemoryReserveHandle;
} USER_APC_OPTION, *PUSER_APC_OPTION;


typedef NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD_EX)(
	IN HANDLE ThreadHandle,
	IN USER_APC_OPTION UserApcOption,
	IN PPS_APC_ROUTINE ApcRoutine,
	IN PVOID SystemArgument1 OPTIONAL,
	IN PVOID SystemArgument2 OPTIONAL,
	IN PVOID SystemArgument3 OPTIONAL
	);

VOID
ApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
);

int main(
	int argc,
	const char** argv
	)
{
	PNT_QUEUE_APC_THREAD_EX NtQueueApcThreadEx;
	USER_APC_OPTION UserApcOption;
	NTSTATUS Status;

	NtQueueApcThreadEx = (PNT_QUEUE_APC_THREAD_EX)(GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueueApcThreadEx"));
	
	if (!NtQueueApcThreadEx) {
		printf("wtf, before win7\n");
		return -1;
	}

	UserApcOption.UserApcFlags = QueueUserApcFlagsSpecialUserApc;

	while (TRUE) {
		//
		// This will force the current thread to execute the special user APC,
		// Although the current thread does not enter alertable state.
		//
		Status = NtQueueApcThreadEx(
					GetCurrentThread(),
					UserApcOption,
					ApcRoutine,
					NULL,
					NULL,
					NULL
				);

		if (!NT_SUCCESS(Status)) {
			printf("NtQueueApcThreadEx Failed! 0x%08X\n", Status);
			return -1;
		}

		//
		// This sleep does not enter alertable state.
		//
		Sleep(500);
	}

	

}

VOID
ApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	)
{
	printf("What? I'm was not alertable!\n");
	Sleep(100);
}