#pragma once
#include "KeApc.h"


typedef VOID
(*PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);


NTSTATUS
SimpleNtQueueApcThread(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

NTSTATUS
SimpleNtWaitForSingleObject(
	HANDLE Event,
	BOOLEAN Alertable,
	PLARGE_INTEGER Timeout
	);