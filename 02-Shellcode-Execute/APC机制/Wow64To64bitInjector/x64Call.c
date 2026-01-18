/*
	This is taken from https://gist.github.com/Cr4sh/76b66b612a5d1dc2c614 with some modifications.
	Credit to github.com/Cr4sh for this implementation and Rewolf http://blog.rewolf.pl/blog/?p=102.
*/

#include <Windows.h>
#include <winternl.h>
#include "x64Call.h"
#pragma warning(push)

//
// Disable illegal instruction size warning.
// This happens because we emit 64 bit instructions in a 32 bit compiler.
//
#pragma warning(disable: 4409) 

#define DB(_val_) __asm __emit (_val_)

// code selectors
#define CS_32   0x23
#define CS_64   0x33

#define RAX     0
#define RCX     1
#define RDX     2
#define RBX     3
#define RSP     4
#define RBP     5
#define RSI     6
#define RDI     7
#define R8      8
#define R9      9
#define R10     10
#define R11     11
#define R12     12
#define R13     13
#define R14     14
#define R15     15

#define X64_PUSH(_r_) DB(0x48 | ((_r_) >> 3)) DB(0x50 | ((_r_) & 7))
#define X64_POP(_r_)  DB(0x48 | ((_r_) >> 3)) DB(0x58 | ((_r_) & 7))

// Switch processor to long mode
#define X64_ENTER_CS(_cs_)                                                                  \
    {                                                                                       \
        DB(0x6a) DB(_cs_)                               /*  push   @cs                  */  \
        DB(0xe8) DB(0x00) DB(0x00) DB(0x00) DB(0x00)    /*  call   $+5                  */  \
        DB(0x83) DB(0x04) DB(0x24) DB(0x05)             /*  add    dword [esp], 5       */  \
        DB(0xcb)                                        /*  retf                        */  \
    }

// Switch processor to WOW64 mode
#define X64_EXIT_CS(_cs_)                                                                   \
    {                                                                                       \
        DB(0xe8) DB(0x00) DB(0x00) DB(0x00) DB(0x00)    /*  call   $+5                  */  \
        DB(0xc7) DB(0x44) DB(0x24) DB(0x04) DB(_cs_)    /*  mov    dword [rsp + 4], @cs */  \
        DB(0x00) DB(0x00) DB(0x00)                                                          \
        DB(0x83) DB(0x04) DB(0x24) DB(0x0d)             /*  add    dword [rsp], 0xD     */  \
        DB(0xcb)                                        /*  retf                        */  \
    }

// 64-bit assembly helpers
#define X64_ENTER() X64_ENTER_CS(CS_64)
#define X64_EXIT() X64_EXIT_CS(CS_32)

#define GET_NEXT_ARG() i < ArgsCount ? Args[i++] : 0

DWORD 
x64_Call(
	DWORD64 ProcAddress, 
	PDWORD64 Args, 
	DWORD ArgsCount
	)
{
	DWORD Retval = 0, OldStack = 0, i = 0;

	DWORD64 _rcx = GET_NEXT_ARG();
	DWORD64 _rdx = GET_NEXT_ARG();
	DWORD64 _r8 = GET_NEXT_ARG();
	DWORD64 _r9 = GET_NEXT_ARG();

	DWORD64 StackArgs = 0;
	DWORD64 StackArgsCount = 0;

	if (ArgsCount > 4)
	{
		StackArgs = (DWORD64)& Args[3];
		StackArgsCount = ArgsCount - 4;
	}

	__asm
	{
		push    ebx
		push    esi
		push    edi

		/**
		 * Stack align for 64-bit mode.
		 */
		 mov     OldStack, esp
		 and esp, 0xfffffff0

		 /**
		  * Swith to the long mode.
		  */
		  X64_ENTER()

		  /**
		   * Copy register arguments.
		   */
		   push    _rcx
		   X64_POP(RCX)

		   push    _rdx
		   X64_POP(RDX)

		   push    _r8
		   X64_POP(R8)

		   push    _r9
		   X64_POP(R9)

		   /**
			* Push stack arguments.
			*/
			push    StackArgs
			X64_POP(RDI)

			push    StackArgsCount
			X64_POP(RSI)

			test    esi, esi
			jz      _call

			_loop_push :

		push[edi + esi * 8]
			sub     esi, 1
			jnz     _loop_push

			_call :
		/**
		 * Perform a function call.
		 */
		push    ProcAddress
			X64_POP(RAX)

			sub     esp, 0x20
			call    eax
			add     esp, 0x20

			/**
			 * Save returned status code.
			 */
			mov     Retval, eax

			/**
			 * Remove syscall arguments from the stack.
			 */
			push    StackArgsCount
			X64_POP(RSI)

			test    esi, esi
			jz      _end

			_loop_pop :

		pop     edi
			sub     esi, 1
			jnz     _loop_pop

			_end :

		/**
		 * Swith back to the 32-bit mode.
		 */
		X64_EXIT()

			mov     esp, OldStack

			pop     edi
			pop     esi
			pop     ebx
	}

	return Retval;
}

//
// This function is used to copy memory from a 64 bit address.
// It happens when we want to read information from the 64 bit TEB / PEB.
// This is done to read the base address and parse the export table of the 64 bit NTDLL.
//
void x64_Memcpy(PVOID Dest, DWORD64 Source, DWORD64 Len)
{
	DWORD64 Destination = (DWORD64)Dest;

	__asm
	{
		push    esi
		push    edi

		/**
		 * Switch to the long mode.
		 */
		 X64_ENTER()

		 /**
		  * Copy register arguments.
		  */
		  push    Destination
		  X64_POP(RDI)

		  push    Source
		  X64_POP(RSI)

		  push    Len
		  X64_POP(RCX)

		  /**
		   * Perform memory regio copying.
		   */
		   rep movsb

		   /**
			* Swith back to the 32-bit mode.
			*/
			X64_EXIT()

			pop     edi
			pop     esi
	}
}

DWORD64 x64_GetTeb(void)
{
	LARGE_INTEGER Retval;
	Retval.QuadPart = 0;

	__asm
	{
		/**
		 * Swith to the long mode.
		 */
		X64_ENTER()

		X64_PUSH(R12)
		pop Retval.LowPart

		/**
		 * Swith back to the 32-bit mode.
		 */
		 X64_EXIT()
	}

	return Retval.QuadPart;
}

#define TEB64_ProcessEnvironmentBlock 0x60

DWORD64 x64_GetPeb(void)
{
	DWORD64 Peb = 0;
	DWORD64 Teb = x64_GetTeb();

	x64_Memcpy(&Peb, Teb + TEB64_ProcessEnvironmentBlock, sizeof(Peb));

	return Peb;
}

typedef DWORD64 PTR64;

#include <pshpack8.h>

typedef struct _LIST_ENTRY_64
{
	PTR64 Flink;
	PTR64 Blink;

} LIST_ENTRY_64;

typedef struct _UNICODE_STRING_64
{
	USHORT Length;
	USHORT MaximumLength;
	PTR64 Buffer;

} UNICODE_STRING64,
* PUNICODE_STRING64;

typedef struct _STRING_64
{
	USHORT Length;
	USHORT MaximumLength;
	PTR64 Buffer;

} ANSI_STRING_64,
* PANSI_STRING_64;

typedef struct _LDR_DATA_TABLE_ENTRY_64
{
	LIST_ENTRY_64 InLoadOrderModuleList;
	LIST_ENTRY_64 InMemoryOrderModuleList;
	LIST_ENTRY_64 InInitializationOrderModuleList;
	PTR64 DllBase;
	PTR64 EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING64 FullDllName;
	UNICODE_STRING64 BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	LIST_ENTRY_64 HashLinks;
	PTR64 SectionPointer;
	ULONG CheckSum;
	ULONG TimeDateStamp;

} LDR_DATA_TABLE_ENTRY_64,
* PLDR_DATA_TABLE_ENTRY_64;

typedef struct _PEB_LDR_DATA_64
{
	ULONG Length;
	BOOLEAN Initialized;
	PTR64 SsHandle;
	LIST_ENTRY_64 ModuleListLoadOrder;
	LIST_ENTRY_64 ModuleListMemoryOrder;
	LIST_ENTRY_64 ModuleListInitOrder;

} PEB_LDR_DATA_64,
* PPEB_LDR_DATA_64;

#include <poppack.h>

#define PEB64_Ldr 0x18

PSTR 
GetNameFromFullPath(
	PSTR Path
	)
{
	PSTR Name = Path;

	for (SIZE_T i = 0; i < strlen(Path); i++)
	{
		if (Path[i] == '\\' || Path[i] == '/')
		{
			Name = Path + i + 1;
		}
	}

	return Name;
}


DWORD64 
x64_GetModuleBase(
	PCSTR ModuleName
	)
{
	// get PEB pointer
	PTR64 Peb = x64_GetPeb();
	LIST_ENTRY_64 ListEntry;

	// get loader tables
	PTR64 LdrData = 0;
	x64_Memcpy(&LdrData, Peb + PEB64_Ldr, sizeof(LdrData));

	// get loaded modules list head
	PTR64 Head = LdrData + FIELD_OFFSET(PEB_LDR_DATA_64, ModuleListLoadOrder);
	x64_Memcpy(&ListEntry, Head, sizeof(ListEntry));

	PTR64 Entry = ListEntry.Flink;

	// parse loaded module list
	while (Entry != Head)
	{
		x64_Memcpy(&ListEntry, Entry, sizeof(ListEntry));

		// get module information
		LDR_DATA_TABLE_ENTRY_64 LdrData;
		DWORD64 Addr = (DWORD64)CONTAINING_RECORD(Entry, LDR_DATA_TABLE_ENTRY_64, InLoadOrderModuleList);
		x64_Memcpy(&LdrData, Addr, sizeof(LdrData));

		// get module name
		WCHAR FullDllNameCopy[MAX_PATH];
		DWORD64 dwCopyLen = min((DWORD64)LdrData.FullDllName.Length, sizeof(FullDllNameCopy) - sizeof(WCHAR));
		ZeroMemory(FullDllNameCopy, sizeof(FullDllNameCopy));
		x64_Memcpy(&FullDllNameCopy, LdrData.FullDllName.Buffer, dwCopyLen);

		char FullDllNameAscii[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, FullDllNameCopy, -1, FullDllNameAscii, MAX_PATH, NULL, NULL);
		_strlwr_s(FullDllNameAscii, MAX_PATH - 1);

		if (!strcmp(GetNameFromFullPath(FullDllNameAscii), ModuleName))
		{
			return LdrData.DllBase;
		}

		Entry = ListEntry.Flink;
	}

	return 0;
}

DWORD64 
x64_GetProcAddressEx(
	DWORD64 ModuleBase, 
	PSTR ProcedureName
	)
{
	// get DOS header
	IMAGE_DOS_HEADER DosHeader;
	x64_Memcpy(&DosHeader, ModuleBase, sizeof(DosHeader));

	// get NT headers
	IMAGE_NT_HEADERS64 Headers;
	x64_Memcpy(&Headers, ModuleBase + DosHeader.e_lfanew, sizeof(Headers));

	DWORD ExportAddr = Headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD ExportSize = Headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	if (ExportAddr)
	{
		// get export directory
		IMAGE_EXPORT_DIRECTORY Export;
		x64_Memcpy(&Export, ModuleBase + ExportAddr, sizeof(Export));

		// parse exports
		for (DWORD i = 0; i < Export.NumberOfFunctions; i++)
		{
			// get function name
			DWORD NameAddr = 0;
			x64_Memcpy(&NameAddr, ModuleBase + Export.AddressOfNames + i * sizeof(DWORD), sizeof(NameAddr));

			char CurrentProcedureName[MAX_PATH];
			ZeroMemory(CurrentProcedureName, sizeof(CurrentProcedureName));
			x64_Memcpy(&CurrentProcedureName, ModuleBase + NameAddr, strlen(ProcedureName) + 1);

			if (!strcmp(CurrentProcedureName, ProcedureName))
			{
				// get function address
				USHORT Ordinal = 0;
				x64_Memcpy(&Ordinal, ModuleBase + Export.AddressOfNameOrdinals + i * sizeof(USHORT), sizeof(Ordinal));

				DWORD Addr = 0;
				x64_Memcpy(&Addr, ModuleBase + Export.AddressOfFunctions + Ordinal * sizeof(DWORD), sizeof(Addr));

				// check for the forwarded export
				if (Addr > ExportAddr &&
					Addr < ExportAddr + ExportSize)
				{
					return 0;
				}

				return ModuleBase + Addr;
			}
		}
	}

	return 0;
}

__declspec(align(16))
typedef struct _GET_PROC_ADDRESS_PARAMS
{
	PTR64 FunctionAddress;
	ANSI_STRING_64 FunctionName;
	char Name[MAX_PATH];

} GET_PROC_ADDRESS_PARAMS,
* PGET_PROC_ADDRESS_PARAMS;

typedef NTSTATUS(WINAPI* func_LdrGetProcedureAddress)(
	HMODULE ModuleHandle,
	PANSI_STRING FunctionName,
	WORD Oridinal,
	PVOID* FunctionAddress
	);

DWORD64 m_LdrGetProcedureAddress = 0;

DWORD64 x64_GetProcAddress(DWORD64 ModuleBase, PCSTR ProcedureName)
{
	if (m_LdrGetProcedureAddress == 0)
	{
		// get ntdll!LdrGetProcedureAddress()
		DWORD64 Ntdll = x64_GetModuleBase("ntdll.dll");
		m_LdrGetProcedureAddress = x64_GetProcAddressEx(Ntdll, "LdrGetProcedureAddress");
		if (m_LdrGetProcedureAddress == 0)
		{
			return 0;
		}
	}

	/*
		Arguments addresses must have a proper alignment, so
		we allocating them at separate memory page instead of the stack.
	*/
	PGET_PROC_ADDRESS_PARAMS Params = (PGET_PROC_ADDRESS_PARAMS)VirtualAlloc(
		NULL, sizeof(GET_PROC_ADDRESS_PARAMS),
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE
	);
	if (Params == NULL)
	{
		return 0;
	}

	// setup ntdll!LdrGetProcedureAddress() arguments
	strcpy_s(Params->Name, sizeof(Params->Name), ProcedureName);

	Params->FunctionName.Buffer = (PTR64)& Params->Name;
	Params->FunctionName.MaximumLength =
		Params->FunctionName.Length = (USHORT)strlen(Params->Name);

	Params->FunctionAddress = 0;

	DWORD64 Args[] =
	{
		ModuleBase,
		(DWORD64)& Params->FunctionName, 0,
		(DWORD64)& Params->FunctionAddress
	};

	// perform x64 function call
	DWORD64 Status = x64_Call(m_LdrGetProcedureAddress, Args, 4);
	DWORD64 Retval = Params->FunctionAddress;

	VirtualFree(Params, 0, MEM_RELEASE);

	if (NT_SUCCESS(Status))
	{
		return Retval;
	}

	return 0;
}

DWORD64
x64_GetSyscallAddress(
	PCSTR SyscallName
	)
{
	return x64_GetProcAddress(x64_GetModuleBase("ntdll.dll"), SyscallName);
}

NTSTATUS
x64_InvokeSyscall(
	DWORD64 SyscallAddress,
	PVOID Args,
	DWORD ArgsSize
	)
{
	PVOID AlignedParameters;

	if (!SyscallAddress) {
		return STATUS_INVALID_PARAMETER;
	}

	AlignedParameters = VirtualAlloc(
					NULL, 
					ArgsSize,
					MEM_COMMIT | MEM_RESERVE,
					PAGE_READWRITE
				);

	if (!AlignedParameters) {
		return STATUS_NO_MEMORY;
	}

	RtlCopyMemory(AlignedParameters, Args, ArgsSize);

	DWORD Ret = x64_Call(SyscallAddress, (PDWORD64)AlignedParameters, ArgsSize / sizeof(DWORD64));

	VirtualFree(AlignedParameters, 0, MEM_RELEASE);

	return (NTSTATUS)Ret;
}



DWORD64
x64_GetNtdllProcedure(
	PCSTR ProcedureName
	)
{
	return x64_GetProcAddress(x64_GetModuleBase("ntdll.dll"), ProcedureName);
}

//
// Read the comment at the top.
//
#pragma warning(pop)