#include <windows.h>
#include <winioctl.h>
#include <SimpleUserApcDriver/SimpleUserApcControl.h>
#include <stdio.h>
#include <winternl.h>

VOID
MyCustomApc(
	ULONG_PTR dwData
)
{
	printf("MyCustomApc!\n");
}

NTSTATUS
DriverWaitForEvent(
	HANDLE EventHandle,
	BOOLEAN Alertable,
	LARGE_INTEGER Timeout
)
{

	HANDLE ApcDeviceHandle = NULL;
	NTSTATUS Status;
	SIMPLE_USER_APC_WAIT WaitArgs;
	IO_STATUS_BLOCK IoStatusBlock;


	RtlZeroMemory(&WaitArgs, sizeof(WaitArgs));
	RtlZeroMemory(&IoStatusBlock, sizeof(IoStatusBlock));

	WaitArgs.Event = EventHandle;
	WaitArgs.Alertable = Alertable;
	WaitArgs.Timeout = Timeout;

	ApcDeviceHandle = CreateFileA(
		"\\\\.\\" SIMPLE_USER_APC_DEVICE_NAME_A,
		FILE_ALL_ACCESS,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (ApcDeviceHandle == INVALID_HANDLE_VALUE) {
		printf("CreateFileA: Cannot open device 0x%08X\n", GetLastError());
		exit(-1);
	}

	Status = NtDeviceIoControlFile(
		ApcDeviceHandle,
		NULL,
		NULL,
		NULL,
		&IoStatusBlock,
		IOCTL_SIMPLE_USER_APC_WAIT,
		&WaitArgs,
		sizeof(WaitArgs),
		NULL,
		0
	);

	if (Status = STATUS_USER_APC) {
		printf("STATUS_USER_APC!\n");
	}
	else {
		exit(-1);
	}

	CloseHandle(ApcDeviceHandle);
	return Status;
}