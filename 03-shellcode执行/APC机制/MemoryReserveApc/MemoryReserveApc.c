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

typedef
NTSTATUS
(NTAPI *PNT_QUEUE_APC_THREAD_EX)(
	IN HANDLE ThreadHandle,
	IN HANDLE MemoryReserveHandle,
	IN PPS_APC_ROUTINE ApcRoutine,
	IN PVOID SystemArgument1 OPTIONAL,
	IN PVOID SystemArgument2 OPTIONAL,
	IN PVOID SystemArgument3 OPTIONAL
	);

typedef enum _MEMORY_RESERVE_OBJECT_TYPE {
	MemoryReserveObjectTypeUserApc,
	MemoryReserveObjectTypeIoCompletion
} MEMORY_RESERVE_OBJECT_TYPE, PMEMORY_RESERVE_OBJECT_TYPE;

typedef
NTSTATUS
(NTAPI *PNT_ALLOCATE_RESERVE_OBJECT)(
	__out PHANDLE MemoryReserveHandle,
	__in_opt POBJECT_ATTRIBUTES ObjectAttributes,
	__in ULONG Type
);

VOID
ExampleApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

PNT_ALLOCATE_RESERVE_OBJECT NtAllocateReserveObject;
PNT_QUEUE_APC_THREAD_EX NtQueueApcThreadEx;

int main(
	int argc,
	const char** argv
	)
{
	NTSTATUS Status;
	HANDLE MemoryReserveHandle;

	NtQueueApcThreadEx = (PNT_QUEUE_APC_THREAD_EX)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueueApcThreadEx");
	NtAllocateReserveObject = (PNT_ALLOCATE_RESERVE_OBJECT)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtAllocateReserveObject");
	
	if (!NtQueueApcThreadEx || !NtAllocateReserveObject) {
		printf("wtf before win7.\n");
		exit(0x1337);
	}

	Status = NtAllocateReserveObject(&MemoryReserveHandle, NULL, MemoryReserveObjectTypeUserApc);

	if (!NT_SUCCESS(Status)) {
		printf("NtAllocateReserveObject Failed! 0x%08X\n", Status);
		return -1;
	}

	while (TRUE) {
		//
		// Queue the APC to the current thread.
		//
		Status = NtQueueApcThreadEx(
					GetCurrentThread(),
					MemoryReserveHandle,
					ExampleApcRoutine,
					NULL,
					NULL,
					NULL
				);

		if (!NT_SUCCESS(Status)) {
			printf("NtQueueApcThreadEx Failed! 0x%08X\n", Status);
			return -1;
		}

		//
		// Enter alertable state to execute the APC.
		//
		SleepEx(0, TRUE);
	}

	return 0;
}

VOID
ExampleApcRoutine(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
)
{
	Sleep(500); 

	printf("This is the weird loop!\n");
}