#include "PeParser.h"
#include <stdio.h>

PBYTE
ReadAllFileBytes(
	PCSTR FilePath,
	PDWORD FileSize
)
{
	HANDLE FileHandle;
	PBYTE FileAllocation;
	DWORD NumberOfBytesRead;

	FileHandle = CreateFileA(
		FilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (FileHandle == INVALID_HANDLE_VALUE) {
		printf("Cannot find wow64 kernel32 DLL 0x%08X\n", GetLastError());
		exit(-1);
	}

	*FileSize = GetFileSize(FileHandle, NULL);

	if (*FileSize == INVALID_FILE_SIZE) {
		printf("Cannot find wow64 kernel32 DLL size 0x%08X\n", GetLastError());
		exit(-1);
	}

	FileAllocation = malloc(*FileSize);

	if (!ReadFile(
		FileHandle,
		FileAllocation,
		*FileSize,
		&NumberOfBytesRead,
		NULL
	)) {
		printf("Cannot read wow64 kernel32 0x%08X\n", GetLastError());
		exit(-1);
	}

	CloseHandle(FileHandle);

	return (PBYTE)FileAllocation;
}

PIMAGE_SECTION_HEADER
GetContainingSection(
	PIMAGE_NT_HEADERS32 ImageNtHeaders,
	ULONG_PTR RelativeVirtualAddress
)
{
	PIMAGE_SECTION_HEADER ImageSectionHeaders = OffsetPtr(ImageNtHeaders, sizeof(IMAGE_NT_HEADERS32));

	for (ULONG i = 0; i < ImageNtHeaders->FileHeader.NumberOfSections; i++) {
		if (RelativeVirtualAddress >= ImageSectionHeaders[i].VirtualAddress &&
			RelativeVirtualAddress < (ImageSectionHeaders[i].VirtualAddress + ImageSectionHeaders[i].SizeOfRawData)) {
			return &ImageSectionHeaders[i];
		}
	}

	return NULL;
}

ULONG
GetImageFileOffset(
	PIMAGE_DOS_HEADER ImageDosHeader,
	ULONG_PTR RelativeVirtualAddress
)
{
	PIMAGE_NT_HEADERS32 ImageNtHeaders = (PIMAGE_NT_HEADERS32)OffsetPtr(ImageDosHeader, ImageDosHeader->e_lfanew);

	if (ImageNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		exit(-1);
	}

	PIMAGE_SECTION_HEADER Section = GetContainingSection(ImageNtHeaders, RelativeVirtualAddress);
	
	ULONG SectionOffset = (ULONG)(RelativeVirtualAddress - Section->VirtualAddress);
	
	return Section->PointerToRawData + SectionOffset;
}

PVOID
GetImageFilePointer(
	PIMAGE_DOS_HEADER ImageDosHeader,
	ULONG_PTR RelativeVirtualAddress
	)
{
	ULONG FileOffset = GetImageFileOffset(ImageDosHeader, RelativeVirtualAddress);

	return OffsetPtr(ImageDosHeader, FileOffset);
}

ULONG
GetExportRva(
	PIMAGE_DOS_HEADER ImageDosHeader,
	PIMAGE_EXPORT_DIRECTORY ImageExportDirectory,
	PCSTR FunctionName
	)
{
	PDWORD AddressOfFunctions = GetImageFilePointer(ImageDosHeader, ImageExportDirectory->AddressOfFunctions);
	PDWORD AddressOfNames = GetImageFilePointer(ImageDosHeader, ImageExportDirectory->AddressOfNames);
	PUSHORT AddressOfNamesOrdinals = GetImageFilePointer(ImageDosHeader, ImageExportDirectory->AddressOfNameOrdinals);
	PCSTR CurrentName;

	for (ULONG i = 0; i < ImageExportDirectory->NumberOfNames; i++) {
		CurrentName = GetImageFilePointer(ImageDosHeader, AddressOfNames[i]);

		if (!strcmp(CurrentName, FunctionName)) {
			DWORD Ordinal;
			DWORD FunctionRva;

			Ordinal = AddressOfNamesOrdinals[i];
			FunctionRva = AddressOfFunctions[Ordinal];

			return FunctionRva;
		}
	}

	return 0;
}

ULONG
GetExportOffset(
	PCSTR LibraryPath,
	PCSTR ExportName
	)
{
	DWORD FileSize;
	ULONG FunctionRva;
	PIMAGE_DOS_HEADER ImageDosHeader;
	PIMAGE_NT_HEADERS32 ImageNtHeaders;
	PIMAGE_DATA_DIRECTORY ExportDataDirectory;
	PIMAGE_EXPORT_DIRECTORY ExportDirectory;

	ImageDosHeader = (PIMAGE_DOS_HEADER)ReadAllFileBytes(LibraryPath, &FileSize);

	if (FileSize <= 1000 ||
		ImageDosHeader->e_magic != IMAGE_DOS_SIGNATURE ||
		(ULONG)ImageDosHeader->e_lfanew >= (FileSize - sizeof(IMAGE_NT_HEADERS32))) {
		exit(-1);
	}

	ImageNtHeaders = (PIMAGE_NT_HEADERS32)OffsetPtr(ImageDosHeader, ImageDosHeader->e_lfanew);

	if (ImageNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		exit(-1);
	}

	ExportDataDirectory = (PIMAGE_DATA_DIRECTORY)(&ImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);
	
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)GetImageFilePointer(ImageDosHeader, ExportDataDirectory->VirtualAddress);

	FunctionRva = GetExportRva(ImageDosHeader, ExportDirectory, ExportName);

	free(ImageDosHeader);

	return FunctionRva;
}



BOOLEAN
Is32bitDll(
	PCSTR DllFilePath
	)
{
	CHAR DllBuffer[512];
	DWORD NumberOfBytesRead;
	HANDLE DllFileHandle;

	DllFileHandle = CreateFileA(
		DllFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (DllFileHandle == INVALID_HANDLE_VALUE) {
		printf("Cannot open file: 0x%08X\n", GetLastError());
		exit(-1);
	}

	if (!ReadFile(
		DllFileHandle,
		&DllBuffer[0],
		sizeof(DllBuffer),
		&NumberOfBytesRead,
		NULL
	)) {
		printf("Cannot read the DLL file. 0x%08X\n", GetLastError());
		exit(-1);
	}

	CloseHandle(DllFileHandle);
	DllFileHandle = NULL;

	PIMAGE_DOS_HEADER ImageDosHeader = (PIMAGE_DOS_HEADER)&DllBuffer[0];

	if (ImageDosHeader->e_magic != IMAGE_DOS_SIGNATURE || ImageDosHeader->e_lfanew >= 500) {
		printf("Invalid PE file\n");
		exit(-1);
	}

	PIMAGE_NT_HEADERS ImageNtHeaders = (PIMAGE_NT_HEADERS)OffsetPtr(ImageDosHeader, ImageDosHeader->e_lfanew);

	if (ImageNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		printf("Invalid PE file\n");
		exit(-1);
	}

	if (ImageNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_I386) {
		return TRUE;

	}
	else if (ImageNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64) {
		return FALSE;
	}
	else {
		printf("Invalid PE file.\n");
		exit(-1);
	}

}