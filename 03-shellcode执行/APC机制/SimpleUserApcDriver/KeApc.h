#pragma once
#include <ntifs.h>

typedef enum _KAPC_ENVIRONMENT {
	OriginalApcEnvironment,
	AttachedApcEnvironment,
	CurrentApcEnvironment,
	InsertApcEnvironment
} KAPC_ENVIRONMENT;

typedef
VOID
(*PKNORMAL_ROUTINE) (
	IN PVOID NormalContext,
	IN PVOID SystemArgument1,
	IN PVOID SystemArgument2
	);

typedef
VOID
(*PKKERNEL_ROUTINE) (
	IN PKAPC Apc,
	IN OUT PKNORMAL_ROUTINE* NormalRoutine,
	IN OUT PVOID* NormalContext,
	IN OUT PVOID* SystemArgument1,
	IN OUT PVOID* SystemArgument2
	);

typedef
VOID
(*PKRUNDOWN_ROUTINE) (
	IN  PKAPC Apc
	);


//
// KeInitializeApc:
//
//	This function initializes the members of the KAPC object.
//
//	Apc: The pointer to the APC object that was allocated in a non-paged area.
//
//  Thread: The pointer to the target thread object.
//
//  Environment: Not relevant to user APCs - OriginalApcEnvironment.
//
//  RundownRoutine: A function that should free the APC. This function will run in case 
//					the thread terminates and the APC did not execute.
//
//	KernelRoutine: A function that executes at APC_LEVEL before the user APC is delivered to 
//				   the user mode thread. This function should free the APC. 
//
//	NormalRoutine: A pointer to the APC routine in user mode. 
//
//	ApcMode: The mode of the APC. For user mode APCs, set to UserMode.
//
//	NormalContext: A parameter that is passed as the first argument of the NormalRoutine.
//
VOID
KeInitializeApc(
	IN  PKAPC Apc,
	IN  PKTHREAD Thread,
	IN  KAPC_ENVIRONMENT Environment,
	IN  PKKERNEL_ROUTINE KernelRoutine,
	IN  PKRUNDOWN_ROUTINE RundownRoutine OPTIONAL,
	IN  PKNORMAL_ROUTINE NormalRoutine OPTIONAL,
	IN  KPROCESSOR_MODE ApcMode OPTIONAL,
	IN  PVOID NormalContext OPTIONAL
);



//
// KeInsertQueueApc:
//
//	Apc: The pointer to the APC object that was initialized using KeInitializeApc.
//
//	SystemArgument1: This is the second argument of the APC routine in user mode.
//
//	SystemArgument2: This is the third argument of the APC routine in user mode.
//
//	Increment: Optional priority increment that is given to the thread in case the thread is signaled.
//
//
BOOLEAN
KeInsertQueueApc(
	IN  PKAPC Apc,
	IN  PVOID SystemArgument1,
	IN  PVOID SystemArgument2,
	IN  KPRIORITY Increment
);