#include "SimpleUserApc.h"

NTSTATUS
SimpleNtQueueApcThread(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	PKAPC Apc = NULL;
	PETHREAD TargetThread = NULL;
	BOOLEAN Inserted = FALSE;

	//
	// Obtain pointer to KTHREAD of the target thread.
	// Verify the handle has THREAD_SET_CONTEXT access.
	//
	Status = ObReferenceObjectByHandle(
		ThreadHandle,
		THREAD_SET_CONTEXT,
		*PsThreadType,
		UserMode,
		&TargetThread,
		NULL
	);

	if (!NT_SUCCESS(Status)) {
		TargetThread = NULL;
		goto Cleanup;
	}

	//
	// Allocate the KAPC object which represents the APC object in the non-paged pool.
	//
	Apc = ExAllocatePoolWithTag(
		NonPagedPoolNx,
		sizeof(KAPC),
		'CPAK'
	);

	if (Apc == NULL) {
		Status = STATUS_NO_MEMORY;
		goto Cleanup;
	}

	//
	// Initialize the members of the KAPC object.
	//
	KeInitializeApc(
		Apc,
		TargetThread,
		OriginalApcEnvironment,
		(PKKERNEL_ROUTINE)ExFreePool,
		(PKRUNDOWN_ROUTINE)ExFreePool,
		ApcRoutine,
		UserMode,
		SystemArgument1
	);

	//
	// Insert the APC into the user queue of the target thread.
	// If the thread is in an alertable wait, signal the thread to execute the APC.
	//
	Inserted = KeInsertQueueApc(Apc, SystemArgument2, SystemArgument3, 0);

	//
	// If the insertion failed (typically because target thread is in 
	// the middle of termination) return an error.
	//
	if (!Inserted) {
		Status = STATUS_UNSUCCESSFUL;
		goto Cleanup;
	}

	Status = STATUS_SUCCESS;

Cleanup:
	if (Apc) {
		ExFreePool(Apc);
	}

	if (TargetThread) {
		ObDereferenceObject(TargetThread);
	}
	
	return Status;
}


//
// A simpler implementation of NtWaitForSingleObject for event objects.
// This can be used to demostrate how user APCs can signal waits.
//
NTSTATUS
SimpleNtWaitForSingleObject(
	HANDLE Object,
	BOOLEAN Alertable,
	PLARGE_INTEGER Timeout
	)
{
	PKEVENT UserEvent = NULL;
	NTSTATUS Status;

	Status = ObReferenceObjectByHandle(
				Object,
				SYNCHRONIZE,
				*ExEventObjectType,
				UserMode,
				&UserEvent,
				NULL
			);

	if (!NT_SUCCESS(Status)) {
		goto Cleanup;
	}

	Status = KeWaitForSingleObject(
				UserEvent,
				UserRequest,
				UserMode,
				Alertable,
				Timeout
			);

Cleanup:
	if (UserEvent) {
		ObDereferenceObject(UserEvent);
	}

	return Status;
}