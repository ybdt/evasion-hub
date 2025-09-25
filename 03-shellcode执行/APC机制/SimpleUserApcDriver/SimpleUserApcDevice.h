#pragma once
#include <ntifs.h>

NTSTATUS
SimpleUserApcInitializeDevice(
	PDRIVER_OBJECT DriverObject
	);

VOID
SimpleUserApcDeleteDevice(
	VOID
	);