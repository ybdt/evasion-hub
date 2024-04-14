-masm=dialect
Output assembly instructions using selected dialect. Also affects which dialect is used for basicasm (see Basic Asm — Assembler Instructions Without Operands) and
extended asm (see Extended Asm - Assembler Instructions with C Expression Operands). Supported choices (in dialect order) are ‘att’ or ‘intel’, The default is ‘att’.
Darwin does not support ‘intel’.

-w   不生成任何警告信息

-s   Remove all symbol table and relocation information from the executable.

-llibrary
-l library
Search the library named library when linking. (The second alternative with the library as a separate argument is only for POSIX compliance and is not recommended.)
The -l option is passed directly to the linker by GCC. Refer to your linker documentation for exact details. The general description below applies to the GNU linker.
The linker searches a standard list of directories for the library. The directories searched include several standard system directories plus any that you specify with -L.
Static libraries are archives of object files, and have file names like liblibrary.a. Some targets also support shared libraries, which typically have names like liblibrary.so.
If both static and shared libraries are found, the linker gives preference to linking with the shared library unless the -static option is used.
It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are specified.
Thus, ‘foo.o -lz bar.o’ searches library ‘z’ after file foo.o but before bar.o. If bar.o refers to functions in ‘z’, those functions may not be loaded.

不指定时默认为-O0   不进行优化处理，减少代码编译时间并保留调试信息
-O或-O1   优化生成代码
-O2   进一步优化
-O3   比-O2更进一步优化，包括inline函数
参考链接：https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

x86_64-w64-mingw32-gcc -o SysWhispers3WinHttp.exe syscalls64.c SysWhispers3WinHttp.c -masm=intel -w -s -lwinhttp -O1