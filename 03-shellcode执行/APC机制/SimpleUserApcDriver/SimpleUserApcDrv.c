#include <ntifs.h>
#include "SimpleUserApcDevice.h"

NTSTATUS
SimplerUserApcDriverUnload(
	PDRIVER_OBJECT DriverObject
	);

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryKey
	)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryKey);
	
	DriverObject->DriverUnload = SimplerUserApcDriverUnload;

	return SimpleUserApcInitializeDevice(DriverObject);
}

NTSTATUS
SimplerUserApcDriverUnload(
	PDRIVER_OBJECT DriverObject
	)
{
	UNREFERENCED_PARAMETER(DriverObject);

	SimpleUserApcDeleteDevice();

	return STATUS_SUCCESS;
}