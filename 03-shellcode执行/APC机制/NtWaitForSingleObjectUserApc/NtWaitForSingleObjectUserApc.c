#include <Windows.h>
#include <winternl.h>
#pragma warning(push)
#pragma warning(disable: 4005) // macro redefinition
#include <ntstatus.h>
#pragma warning(pop)
#include <stdio.h>

DWORD
WINAPI
WorkerThread(
	PVOID EventHandleArg
);

VOID
UserApc(
	VOID
);

HANDLE gEventHandle;



int main() 
{
	HANDLE ThreadHandle;

	gEventHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	ThreadHandle = CreateThread(NULL, 0, WorkerThread, gEventHandle, 0, NULL);

	
	for (int i=0; i<10; i++){
		Sleep(500);
		
		QueueUserAPC((PAPCFUNC)UserApc, ThreadHandle, 0);
	}

}

VOID
UserApc(
	VOID
)
{
	printf("User APC is delivered.\n");
}

DWORD
WINAPI
WorkerThread(
	PVOID ThreadParam
	) 
{
	UNREFERENCED_PARAMETER(ThreadParam);
	
	NTSTATUS Status;

	while (TRUE) {
		Status = NtWaitForSingleObject(gEventHandle, TRUE, NULL);

		if (Status == STATUS_USER_APC) {
			printf("Status == STATUS_USER_APC\n");
		}
		else {
			printf("Status == 0x%08X\n", Status);
		}
	}
}