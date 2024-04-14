# 免杀对抗
## 思路总结
### 01 睡眠
```
在适当位置添加睡眠语句
C语言 -> Sleep(1000);
```
### 02 垃圾代码
```
添加正常代码段，干扰杀软检测
```
### 03 反沙箱
```
创建启动密码来反沙箱，代码如下
if (argc != 2) {
    printf("[-] Need password");
    return 0;
}
else if (strcmp(argv[1], "dajipeiniwan") != 0) {
    printf("[-] Password incorrect");
    return 0;
}
else {
    pass;
    return 0;
}
```
```
检查当前所在系统的内存大小和CPU核心数
```
```
检查当前所在系统的进程数是否小于40（用来反Defender沙箱）
```