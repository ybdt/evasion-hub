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
} USER_APC_OPTION, * PUSER_APC_OPTION;


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


PNT_QUEUE_APC_THREAD_EX NtQueueApcThreadEx;
RTL_CRITICAL_SECTION gItemsListLock;
DWORD ItemList[1000];
DWORD CurrentItemIndex;

DWORD
WINAPI
UseListWorker(
	PVOID Parameter
	);

VOID
ChangeListApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
);

int 
main(
	VOID
	) 
{
	HANDLE ThreadHandle;
	USER_APC_OPTION UserApcOption;
	NTSTATUS Status;

	NtQueueApcThreadEx = (PNT_QUEUE_APC_THREAD_EX)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueueApcThreadEx");
	
	if (!NtQueueApcThreadEx) {
		printf("wtf? before win7.\n");
		return -1;
	}

	RtlZeroMemory(&ItemList, sizeof(ItemList));
	CurrentItemIndex = 0;
	InitializeCriticalSection(&gItemsListLock);

	ThreadHandle = CreateThread(NULL, 0, UseListWorker, NULL, 0, NULL);

	while (TRUE) {
		UserApcOption.UserApcFlags = QueueUserApcFlagsSpecialUserApc;

		Status = NtQueueApcThreadEx(
					ThreadHandle,
					UserApcOption,
					ChangeListApcRoutine,
					NULL,
					NULL,
					NULL
				);

		if (!NT_SUCCESS(Status)) {
			printf("NtQueueApcThreadEx Failed! 0x%08X\n", Status);
			exit(-1);
		}

		Sleep(200);
	}

}

DWORD
WINAPI
UseListWorker(
	PVOID Parameter
	)
{

	while (TRUE) {
		EnterCriticalSection(&gItemsListLock);

		for (ULONG i = 0; i < 1000; i++) {
			ItemList[i] = 1;
		}

		Sleep(1000);

		for (ULONG i = 0; i < 1000; i++) {
			if (ItemList[i] != 1) {
				printf("What?? I acquired the lock, how come the array changed?\n");
				exit(-1);
			}
		}

		LeaveCriticalSection(&gItemsListLock);

		Sleep(500);
	}

}

VOID
ChangeListApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	)
{
	EnterCriticalSection(&gItemsListLock);

	for (ULONG i = 0; i < 1000; i++) {
		ItemList[i] = 2;
	}

	LeaveCriticalSection(&gItemsListLock);
}