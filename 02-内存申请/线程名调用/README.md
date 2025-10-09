# Thread Name-Calling Injection

[![Build status](https://ci.appveyor.com/api/projects/status/k4ff2bndq4juwnpc?svg=true)](https://ci.appveyor.com/project/hasherezade/thread-namecalling)

Remote shellcode injection technique, using Thread Name (a.k.a. Thread Description)

The code to be injected is passed as a thread description to the target (with `SetThreadDescription`). Then, a function `GetThreadDescription` is called remotely on the target, via APC, causing the description buffer to be copied into the target’s working set. After making the buffer executable, it is run using another APC call.

**Details: https://research.checkpoint.com/2024/thread-name-calling-using-thread-name-for-offense/**

## Remote write via Thread Name

The buffer is injected into the remote process without the need of having the [write access right (`PROCESS_VM_WRITE`)](https://learn.microsoft.com/en-us/windows/win32/procthread/process-security-and-access-rights).

![](img/animation.gif)

## Modules

+ `thread_namecaller` - implementation of Thread Name-Calling injection. Injects a shellcode that pops a calc into a process selected by the PID
+ `dll_inj` - a DLL injection variant. The path to the DLL is written into the remote process via Thread Name
+ `thread_receive` - a demo target application, with a [set of various mitigation policies](https://github.com/hasherezade/thread_namecalling/blob/master/thread_receive/main.cpp#L11)

### Demo

`thread_namecaller` in action:
+  https://www.youtube.com/watch?v=JjVSMin8kFU

`dll_inj` in action:
+  https://www.youtube.com/watch?v=8cSNgE3gZxY
