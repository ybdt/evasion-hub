#include <Windows.h>
#include <winternl.h>
#include <stdio.h>

typedef
NTSTATUS
(*PNT_TEST_ALERT)(
		VOID
	);

VOID
NTAPI
ApcCode(
	ULONG_PTR dwData
	)
{
	printf("Hello from APC!\n");
}


int main(
	int argc,
	const char** argv
	)
{
	HMODULE hNtdll = GetModuleHandle("ntdll.dll");

	PNT_TEST_ALERT NtTestAlert = (PNT_TEST_ALERT)(GetProcAddress(hNtdll, "NtTestAlert"));
	
	printf("Queueing APC..\n");

	QueueUserAPC(ApcCode, GetCurrentThread(), 0);
	
	printf("Calling NtTestAlert...\n");

	NtTestAlert();

	printf("After NtTestAlert..\n");

	return 0;

}