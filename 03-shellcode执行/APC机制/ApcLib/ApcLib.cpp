#include "ApcLib.h"

VOID
InitializeApi(
	VOID
	)
{
	HMODULE NtdllHandle = GetModuleHandle("ntdll.dll");
	HMODULE Kernel32Handle = GetModuleHandle("kernel32.dll");

	NtGetNextThread = (PNT_GET_NEXT_THREAD)GetProcAddress(NtdllHandle, "NtGetNextThread");
	NtQueueApcThread = (PNT_QUEUE_APC_THREAD)GetProcAddress(NtdllHandle, "NtQueueApcThread");
	NtQueueApcThreadEx = (PNT_QUEUE_APC_THREAD_EX)GetProcAddress(NtdllHandle, "NtQueueApcThreadEx");
	LoadLibraryAPtr = GetProcAddress(Kernel32Handle, "LoadLibraryA");
}
