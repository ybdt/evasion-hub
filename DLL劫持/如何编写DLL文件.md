VS2022创建C++ DLL应用

# 编写方式1
dllmain.cpp
```
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

extern "C" _declspec(dllexport) void __cdecl daji();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void daji()
{
    std::cout << "abc" << std::endl;
}
```

# 编写方式2
pch.h
```
// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H

extern "C"
{
    _declspec(dllexport) void __cdecl daji();
}
```
pch.cpp
```
// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

void daji() {
    std::cout << "abc" << std::endl;
}
```