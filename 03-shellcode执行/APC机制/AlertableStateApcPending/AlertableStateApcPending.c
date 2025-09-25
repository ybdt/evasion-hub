#include <Windows.h>
#include <winternl.h>
#include <stdio.h>

VOID
ApcCode(
	ULONG_PTR dwData
	)
{
	UNREFERENCED_PARAMETER(dwData);

	printf("Hello from APC!\n");
}	

int main(
	int argc, 
	const char** argv
	)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	HANDLE EventHandle;
	NTSTATUS Status;

	printf("Queueing APC..\n");

	QueueUserAPC(ApcCode, GetCurrentThread(), 0);

	EventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	printf("Sleeping forever...\n");

	Status = NtWaitForSingleObject(EventHandle, TRUE, NULL);
	
	printf("Status = 0x%08X\n", Status);

	return 0;
}