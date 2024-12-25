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
# Rookit
```
https://github.com/m0nad/Diamorphine

https://github.com/bytecode77/r77-rootkit
```

# 白加黑
```
【工具推荐】 - ZeroEye3.3免杀辅助利器，自动化找白加黑，支持生成模板。
https://mp.weixin.qq.com/s/D0x4XSr37cMrv7Y4ScRqTg
https://github.com/ImCoriander/ZeroEye

【工具推荐】 - 比Everything弱一点的自动化白加黑工具（灰梭子）
https://mp.weixin.qq.com/s?__biz=MzkyNDUzNjk4MQ==&mid=2247483925&idx=1&sn=7424113417378915f17155260bdeef67&chksm=c1d51beff6a292f9cbb906cbaa2a55925d7ac1faeb9860b2d340b95cd33a2a0478d494daf711&scene=21#wechat_redirect
```