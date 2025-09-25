# APC Internals Research Code

This repo will contain all the code related to the APC research including reverse engineered sources.

### ApcLib

A library with common functionality related to the supplied samples.

### ApcDllInjector

Allows to inject a DLL using a user mode APC from user mode.

```
ApcDllInjector.exe <native/win32/special> <process_id> <dll_path> [thread_id]
```

- native: Uses NtQueueApcThread
- win32: Uses QueueUserAPC
- special: Uses NtQueueApcThreadEx with the special flag.

The dll_path is written to the remote process using WriteProcessMemory.

The target of the APC is LoadLibrary.

### ApcRaceConditionExample

This is an example of a possible race condition that can occur if Special APCs are used without caution. 

### ApcRoutineUseContextRecord

This is an example of an APC routine that uses the hidden context argument. It prints the RIP at the point the APC "interrupted" the
thread.

### MemoryReserveApc

This is an example of using Memory Reserve object to reuse the memory of a KAPC object.

### SpecialUserApcExample

This is an example showing how special kernel APC is delivered to a thread even if it's not an alertable state.

### InitialNtTestAlert

This shows how we can abuse the NtTestAlert call that is called before the win32 start address of the
thread to execute an APC.

### NtWaitForSingleObjectUserApc

This test shows how NtWaitForSingleObject returns STATUS_USER_APC when an APC is delivered to the thread. 
WaitForSingleObject() is a wrapper that simply ignores this value and waits again.

### InitialNtTestAlertCreateProcessInjection

This is an example of an injection technique that uses the initial NtTestAlert.

### AlertableStateApcPending

This example shows what happens when you enter an alertable state after queueing an APC.

### QueueApcAndNtTestAlert

This example shows how NtTestAlert can be used to execute pending APCs.

### SimpleUserApcDriver

A driver that lets a user mode caller to run 2 functions:

1 - SimpleNtQueueApcThread: A simple implementation that shows how a user APC can be queued from 
kernel mode.

2 - SimpleNtWaitForSingleObject: A simple implementation of NtWaitForSingleObject for event objects.

### SimpleUserApcDriverTester

Test the SimpleNtQueueApcThread function.

### SimpleUserApcWaitTester

Test the SimpleNtWaitForSingleObject function.

### 32bitApc

A x86 sample that uses QueueUserAPC. Can be used to debug the Wow64 APC.

### NullApcRoutine

A sample that can be used to debug a user APC with a null ApcRoutine. This is 
interesting because it actually creates a KernelMode APC.

### QueueMultipleUserAPCs

A sample that shows the behavior with multiple pending APCs.


### Wow64To64bitInjector

Shows how a Wow64 process can queue an APC in a 64 bit process.

### x64ToWow64ApcInjector

Shows how a 64 bit process can queue an APC in a Wow64 process. The APC can be one of 2 kinds:

1. A 64 bit APC. used to execute a 64 bit ApcRoutine.
2. A Wow64 APC: The ApcRoutine should run in a Wow64 environment.