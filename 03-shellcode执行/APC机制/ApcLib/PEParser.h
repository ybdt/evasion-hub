#pragma once
#include <Windows.h>
#include <winternl.h>


FORCEINLINE
PVOID
OffsetPtr(
	PVOID BaseAddress,
	ULONG Offset
)
{
	ULONG_PTR BaseAddressUlong = (ULONG_PTR)BaseAddress;

	return (PVOID)(BaseAddressUlong + Offset);
}

FORCEINLINE
ULONG
OffsetFromBase(
	PVOID BaseAddress,
	PVOID Address
)
{
	ULONG_PTR BaseAddressUlong = (ULONG_PTR)BaseAddress;
	ULONG_PTR AddressUlong = (ULONG_PTR)Address;

	return (ULONG)(AddressUlong - BaseAddressUlong);
}


BOOLEAN
Is32bitDll(
	PCSTR DllFilePath
	);

ULONG
GetExportOffset(
	PCSTR LibraryPath,
	PCSTR ExportName
	);