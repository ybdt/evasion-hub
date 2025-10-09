#pragma once
#include <Windows.h>


ULONG
x64_Call(
	DWORD64 ProcAddress,
	PDWORD64 Args, 
	DWORD ArgsCount
	);

DWORD64
x64_GetSyscallAddress(
	PCSTR SyscallName
	);

NTSTATUS
x64_InvokeSyscall(
	DWORD64 SyscallAddress,
	PVOID Args,
	DWORD ArgsSize
	);

DWORD64 
x64_GetModuleBase(
	PCSTR ModuleName
	);

DWORD64
x64_GetNtdllProcedure(
	PCSTR ProcedureName
	);
