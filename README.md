# 0x01 AV/EDR原理
```
https://blog.deeb.ch/posts/how-edr-works/
https://www.edr-telemetry.com/
```

# 0x02 WinDBG使用
```
https://p.ost2.fyi/
```

# 0x03 免杀技巧
```
01、Loader执行时需要密码【反沙箱对抗】
02、适当睡眠【动态免杀对抗】
03、垃圾代码【静态免杀对抗，类似于花指令、LLVM】
```

# 0x04 LNK钓鱼马免杀
```
https://www.cybereason.com/blog/threat-analysis-taking-shortcuts-using-lnk-files-for-initial-infection-and-persistence
【LNK文件深度解析-钓鱼攻击利用姿势】https://mp.weixin.qq.com/s/-sGRCSoOxP2a9aR0vNoZVw
```

# 0x05 UAC Bypass
```
# 面向个人PC，适用于社工
https://github.com/hackerhouse-opensource/iscsicpl_bypassUAC
```

# 0x06 白加黑
```
https://hijacklibs.net/

【工具推荐】 - ZeroEye3.3免杀辅助利器，自动化找白加黑，支持生成模板。
https://mp.weixin.qq.com/s/D0x4XSr37cMrv7Y4ScRqTg
https://github.com/ImCoriander/ZeroEye

【工具推荐】 - 比Everything弱一点的自动化白加黑工具（灰梭子）
https://mp.weixin.qq.com/s?__biz=MzkyNDUzNjk4MQ==&mid=2247483925&idx=1&sn=7424113417378915f17155260bdeef67&chksm=c1d51beff6a292f9cbb906cbaa2a55925d7ac1faeb9860b2d340b95cd33a2a0478d494daf711&scene=21#wechat_redirect
```

# 0x07 Shellcode Loader
```
https://ericesquivel.github.io/posts/bypass
https://github.com/thomasxm/BOAZ_beta
https://blog.malicious.group/writing-your-own-rdi-srdi-loader-using-c-and-asm/
https://github.com/0xHossam/HuffLoader
https://github.com/UmaRex01/Hit-And-Run
```

# 0x08 AMSI
```
https://practicalsecurityanalytics.com/blog/red-team/
https://github.com/EvilBytecode/Ebyte-AMSI-ProxyInjector
```

# 0x09 COM技术
```
https://mohamed-fakroud.gitbook.io/red-teamings-dojo/abusing-idispatch-for-trapped-com-object-access-and-injecting-into-ppl-processes
```

# 0x10 LLVM
```
https://github.com/obfuscator-llvm/obfuscator
```

# 0x11 奇技淫巧
```
https://cloudbrothers.info/en/edr-silencers-exploring-methods-block-edr-communication-part-1/

# Linux下二进制混淆
    https://github.com/hackerschoice/bincrypter

内存修改

硬件断点
```

# 0x12 Kill AV/EDR
```
https://www.loldrivers.io/

https://github.com/m0nad/Diamorphine
https://github.com/bytecode77/r77-rootkit
https://github.com/eversinc33/Banshee
【白驱动 Kill AV/EDR（上）】https://myzxcg.com/2023/09/白驱动-Kill-AV/EDR上/
【BYOVD ATTACK 学习】https://xz.aliyun.com/news/12373
https://www.binarydefense.com/resources/blog/threadsleeper-suspending-threads-via-gmer64-driver/
https://www.sangfor.com/farsight-labs-threat-intelligence/cybersecurity/what-is-byovd-attacks-2023
https://github.com/MaorSabag/TrueSightKiller
```

# 0x13 AV/EDR模拟
```
https://github.com/BlackSnufkin/LitterBox
```

# 0x14 APT组织
```
揭露天鹅向量（Swan Vector）APT组织：针对中国台湾和日本的多阶段DLL植入攻击
https://mp.weixin.qq.com/s/ZUR7-2OdZcQiq8A8qiptwg
使用的技术：lnk钓鱼、rundll32、api hash、dll劫持、syscall

https://mp.weixin.qq.com/s/S7Iq5DfO7xNX3GPJzwedPw
Operation(润)RUN：“离岸爱国者”的赛博狂欢
```