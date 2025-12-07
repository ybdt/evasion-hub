环境：Win10 22H2 19045.6466

实现了Windows中添加用户，从上层API到底层API：调用命令、通过NetAPI32、通过SAM RPC

其实想通过更深层次添加用户的方式也有，比如SAM.sys驱动、SAM数据库、LSASS进程的内存、甚至是安全子系统，但需要你有足够的Windows功底

完整源码和编译后的EXE均提供，EXE执行后如下图

![image](./pic/01.png)

![image](./pic/02.png)

![image](./pic/03.png)