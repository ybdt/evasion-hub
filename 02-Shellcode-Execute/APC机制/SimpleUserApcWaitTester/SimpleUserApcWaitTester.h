#pragma once
#include <Windows.h>

#define T_RELATIVE(Timeout) ((ULONGLONG)(-((LONGLONG)Timeout)))
#define T_MILLISECONDS(Milliseconds) (10000*((ULONGLONG)Milliseconds))
#define T_SECONDS(Seconds) (T_MILLISECONDS(1000*((ULONGLONG)Seconds)))

NTSTATUS
DriverWaitForEvent(
	HANDLE EventHandle,
	BOOLEAN Alertable,
	LARGE_INTEGER Timeout
);

VOID
MyCustomApc(
	ULONG_PTR dwData
	);

VOID
UserApcToAlertableWaitingThread(
	VOID
	);


VOID
UserApcToNonAlertableThread(
	VOID
	);	