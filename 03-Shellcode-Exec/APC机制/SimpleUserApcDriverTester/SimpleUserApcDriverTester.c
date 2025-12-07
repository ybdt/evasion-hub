#include <windows.h>
#include <winioctl.h>
#include <SimpleUserApcDriver/SimpleUserApcControl.h>
#include <stdio.h>

VOID
DriverQueueApc(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

DWORD
WINAPI
ApcThread(
	PVOID ThreadArgument
	)
{
	printf("ApcThread.\n");

	return 0;
}

VOID
MyCustomApc(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	)
{
	printf("MyCustomApc!\n");
}

int main(int argc, const char** argv)
{
	
	HANDLE ThreadHandle = CreateThread(
							NULL,
							0,
							ApcThread,
							NULL,
							CREATE_SUSPENDED,
							NULL
						);

	if (ThreadHandle == NULL) {
		printf("CreateThread Failed: 0x%08X\n", GetLastError());
		exit(-1);
	}

	DriverQueueApc(
		ThreadHandle,
		MyCustomApc,
		NULL,
		NULL,
		NULL
	);

	ResumeThread(ThreadHandle);
	WaitForSingleObject(ThreadHandle, INFINITE);
}

VOID
DriverQueueApc(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	)
{

	HANDLE ApcDeviceHandle = NULL;
	SIMPLE_QUEUE_APC_THREAD QueueApcArgs;
	DWORD IoctlBytesReturned;

	RtlZeroMemory(&QueueApcArgs, sizeof(QueueApcArgs));

	QueueApcArgs.ThreadHandle = ThreadHandle;
	QueueApcArgs.ApcRoutine = ApcRoutine;
	QueueApcArgs.SystemArgument1 = SystemArgument1;
	QueueApcArgs.SystemArgument2 = SystemArgument2;
	QueueApcArgs.SystemArgument3 = SystemArgument3;

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

	
	if (!DeviceIoControl(
		ApcDeviceHandle,
		IOCTL_SIMPLE_USER_APC_QUEUE,
		&QueueApcArgs,
		sizeof(QueueApcArgs),
		NULL,
		0,
		&IoctlBytesReturned,
		NULL
	)) {
		printf("DeviceIoControl Failed! 0x%08X\n", GetLastError());
		CloseHandle(ApcDeviceHandle);
		exit(-1);
	}
	
	CloseHandle(ApcDeviceHandle);
}