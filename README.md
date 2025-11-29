# 01-函数地址定位
```
0x01 通过Win32 API

0x02 通过Windows Native API

0x03 通过遍历PEB和EAT

0x04 通过内存中特征匹配
    https://github.com/Teach2Breach/stargate/blob/main/blog.md
```

# AMSI绕过
```
# 待学习
https://github.com/EvilBytecode/Ebyte-AMSI-ProxyInjector
https://www.r-tec.net/r-tec-blog-bypass-amsi-in-2025.html
```

# DLL劫持
```
# 待学习
https://hijacklibs.net/
https://mp.weixin.qq.com/s/D0x4XSr37cMrv7Y4ScRqTg
https://github.com/ImCoriander/ZeroEye
https://mp.weixin.qq.com/s/QFHGYBP8iWGje0nGIYGLhg
https://www.r-tec.net/r-tec-blog-dll-sideloading.html
```

# UAC Bypass

# Payload执行

# BOF

# 进程注入

# BYOVD

# 代码混淆
```
# 商业
Themida   https://www.oreans.com/Themida.php
VMProtect   https://vmpsoft.com/

# 开源
https://github.com/KomiMoe/Arkari
https://github.com/obfuscator-llvm/obfuscator
```

# 基于LLM实现免杀
```
https://mp.weixin.qq.com/s/VVmDDPcChtWF_yA-zv47zQ?click_id=1
https://www.outflank.nl/blog/2025/08/07/training-specialist-models/
```

# Linux/MacOS下免杀对抗
```
# 二进制/Shell脚本混淆器
https://github.com/hackerschoice/bincrypter
```

# 杂七杂八
```
Windows API开发
Windows Native API开发
Windows 16位汇编
Windows 32位汇编
Windows COM
Windows RPC
Windows 内核
IDA Pro 使用
x64dbg 使用
WinDBG 使用


0x01 国家级APT攻击
    https://mp.weixin.qq.com/s/ZUR7-2OdZcQiq8A8qiptwg【揭露天鹅向量（Swan Vector）APT组织：针对中国台湾和日本的多阶段DLL植入攻击，使用的技术：lnk钓鱼、rundll32、api hash、dll劫持、syscall】
    https://mp.weixin.qq.com/s/S7Iq5DfO7xNX3GPJzwedPw
    https://research.checkpoint.com/2025/stealth-falcon-zero-day/

0x02 定位二进制中被AV标识的字节
    https://github.com/rasta-mouse/ThreatCheck
    https://github.com/dobin/avred

0x03 UAC Bypass
    https://github.com/hackerhouse-opensource/iscsicpl_bypassUAC【UACME项目中的RAiLaunchAdminProcess】
    https://www.elastic.co/security-labs/exploring-windows-uac-bypasses-techniques-and-detection-strategies
    https://github.com/zer0antisec/UACBypass/tree/main

0x05 阻断EDR Agent和Server端交流
    https://cloudbrothers.info/en/edr-silencers-exploring-methods-block-edr-communication-part-1/


0x06 WinDBG使用
    https://p.ost2.fyi/
0x13 逆向工程
    https://github.com/DebugPrivilege/InsightEngineering
    0x16 内核调试
    https://www.youtube.com/watch?v=K5abwBNb76k&list=PLUFkSN0XLZ-ka9dfeHWmhqDV-qIns-9uR
    https://www.youtube.com/watch?v=_5c8ErwyqiU&list=PLUFkSN0XLZ-kOQnYJwx3x9wPMDjlv2iSg
    https://www.youtube.com/watch?v=SSerGWQW70c&list=PLUFkSN0XLZ-nl4HEX4_LWG9H_d9vJKkYL


0x08 AV/EDR识别和研究
    https://av.aabyss.cn/
    https://tasklist.pdsec.top/
    http://bypass.tidesec.com/bycms
    https://github.com/Goqi/AvHunt
    https://github.com/FourCoreLabs/EDRHunt
    https://github.com/0xJs/EnumEDR-s
    https://blog.deeb.ch/posts/how-edr-works/
    https://www.edr-telemetry.com/
    https://github.com/BlackSnufkin/LitterBox【一个很好的沙箱环境】
    https://github.com/UmaRex01/HookSentry

0x09 大佬推荐：
    https://synzack.github.io/Blinding-EDR-On-Windows/
    https://mp.weixin.qq.com/s/AAKMYtASCcTfm1DIqTPQLg
    https://github.com/Hagrid29/PELoader
    https://github.com/RWXstoned/LdrShuffle
    https://github.com/fortra/No-Consolation
    https://labs.yarix.com/2025/06/doppelganger-an-advanced-lsass-dumper-with-process-cloning/
    https://www.x86matthew.com/view_post?id=ntsockets
    https://www.akamai.com/blog/security-research/abusing-dmsa-for-privilege-escalation-in-active-directory
    https://github.com/MaLDAPtive/Invoke-Maldaptive
    https://ericesquivel.github.io/posts/bypass
    https://www.darkrelay.com/post/stealth-syscall-execution-bypass-edr-detection
    https://medium.com/@andreabocchetti88/living-off-the-com-type-coercion-abuse-108f988bb00a
    https://github.com/TheWover/donut
    https://github.com/vari-sh/RedTeamGrimoire

0x10 COM
    https://mohamed-fakroud.gitbook.io/red-teamings-dojo/windows-internals/playing-around-com-objects-part-1
    https://googleprojectzero.blogspot.com/2025/01/windows-bug-class-accessing-trapped-com.html
    https://mohamed-fakroud.gitbook.io/red-teamings-dojo/abusing-idispatch-for-trapped-com-object-access-and-injecting-into-ppl-processes
    https://bohops.com/2018/06/28/abusing-com-registry-structure-clsid-localserver32-inprocserver32/
    https://bohops.com/2018/08/18/abusing-the-com-registry-structure-part-2-loading-techniques-for-evasion-and-persistence/
    https://bohops.com/2018/03/17/abusing-exported-functions-and-exposed-dcom-interfaces-for-pass-thru-command-execution-and-lateral-movement/
    https://www.ibm.com/think/x-force/remotemonologue-weaponizing-dcom-ntlm-authentication-coercions
    https://www.ibm.com/think/news/fileless-lateral-movement-trapped-com-objects
    https://medium.com/@andreabocchetti88/living-off-the-com-type-coercion-abuse-108f988bb00a

0x012 线程执行
    https://research.checkpoint.com/2025/waiting-thread-hijacking/
    https://github.com/Friends-Security/RedirectThread


0x15 内存扫描原理
    https://www.blackhillsinfosec.com/avoiding-memory-scanners/


0x17 BOF
    https://github.com/NetSPI/BOF-PE
    https://devco.re/blog/2024/08/23/streaming-vulnerabilities-from-windows-kernel-proxying-to-kernel-part1-en/
    https://devco.re/blog/2024/10/05/streaming-vulnerabilities-from-windows-kernel-proxying-to-kernel-part2-en/
    https://www.ibm.com/think/x-force/little-bug-that-could
    https://www.ibm.com/think/x-force/critically-close-to-zero-day-exploiting-microsoft-kernel-streaming-service
    https://github.com/Mr-Un1k0d3r/EDRs
    https://github.com/tdeerenberg/InlineWhispers3
    https://blog.quarkslab.com/proxyblobing-into-your-network.html
    https://github.com/serge1/COFFI

0x18 RDI/sRDI
    https://github.com/thomasxm/BOAZ_beta
    https://blog.malicious.group/writing-your-own-rdi-srdi-loader-using-c-and-asm/

0x20 AV/EDR致盲
    https://www.loldrivers.io/
    https://github.com/m0nad/Diamorphine
    https://github.com/bytecode77/r77-rootkit
    https://github.com/eversinc33/Banshee
    【白驱动 Kill AV/EDR（上）】https://myzxcg.com/2023/09/白驱动-Kill-AV/EDR上/
    【BYOVD ATTACK 学习】https://xz.aliyun.com/news/12373
    https://www.binarydefense.com/resources/blog/threadsleeper-suspending-threads-via-gmer64-driver/
    https://www.sangfor.com/farsight-labs-threat-intelligence/cybersecurity/what-is-byovd-attacks-2023
    https://github.com/MaorSabag/TrueSightKiller


1. 环境搭建以及逆向方法：
    https://voidsec.com/windows-drivers-reverse-engineering-methodology/
2. 理解IOCTL：
    https://medium.com/@WaterBucket/understanding-ioctls-for-windows-vulnerability-research-exploit-development-c49229b38d8d
3. 深入学习挖掘方法：
    https://blogs.vmware.com/security/2023/10/hunting-vulnerable-kernel-drivers.html
    https://medium.com/@matterpreter/methodology-for-static-reverse-engineering-of-windows-kernel-drivers-3115b2efed83
4. 实例/挖掘过程讲解：
    https://www.cyberark.com/resources/threat-research-blog/inglourious-drivers-a-journey-of-finding-vulnerabilities-in-drivers
5. 其它参考：
    https://www.cyberark.com/resources/threat-research-blog/finding-bugs-in-windows-drivers-part-1-wdm
    https://research.checkpoint.com/2024/breaking-boundaries-investigating-vulnerable-drivers-and-mitigating-risks/
视频(English)：
1. 入门级讲解Windows驱动程序：https://www.youtube.com/watch?v=7Trgnw7HkeE
项目：
1 IOCTL fuzzer：
	1.1 https://github.com/koutto/ioctlbf
	1.2 https://github.com/otavioarj/SIOCTLBF
	1.3 https://github.com/nccgroup/DIBF
2. BYOVD 辅助挖掘工具：https://github.com/ghostbyt3/BYOVDFinder
3. BYOVD 漏洞/实例收集:
	3.1 https://github.com/ZeroMemoryEx/Blackout
	3.2 https://github.com/BlackSnufkin/BYOVD
	3.3 https://github.com/vxcall/kur
4. BYOVD 利用 ：
	4.1 mapper ：
		4.1.1 https://github.com/shaygitub/ShayMapper
		4.1.2 https://github.com/TheCruZ/kdmapper
	4.2 Rootkit: https://github.com/ColeHouston/Sunder
	4.3 其它：
		4.3.1 https://github.com/1003761249/CheatEngine-With-kdmapper
		4.3.2 https://github.com/fuluke/Kdmapper-Bypass360
		4.3.3 https://github.com/FiYHer/kdmapper
		4.3.4 https://github.com/TygoL/kdmapper-mdl
		4.3.5 https://github.com/zorftw/kdmapper-rs
		4.3.6 https://github.com/rmccrystal/kdmapper-rs

0x21 2024.11.11推荐
    https://github.com/NUL0x4C/AtomLdr   此项目主要是利用indirect syscalls gadgets和其他技术进行behavior evasion
    https://github.com/kyleavery/AceLdr   此项目主要是memory scanner evasion
    再结合LLVM混淆进行静态免杀 + 沙箱检测 + 白利用 + 调用栈欺骗，应该会是一个不错的Loader

内存躲避
    （对内存中的shellcode频繁变动访问权限）https://github.com/mgeeky/ShellcodeFluctuation

# 进程注入
    # APC注入
        https://repnz.github.io/posts/apc/user-apc/
        https://repnz.github.io/posts/apc/kernel-user-apc-api/
        https://repnz.github.io/posts/apc/wow64-user-apc/
        https://github.com/repnz/apc-research
    # 异常
        https://bruteratel.com/research/2024/10/20/Exception-Junction/
        https://github.com/passthehashbrowns/VectoredExceptionHandling
    # 用户层无敌方案
        https://www.malwaretech.com/2024/02/bypassing-edrs-with-edr-preload.html
        https://www.outflank.nl/blog/2024/10/15/introducing-early-cascade-injection-from-windows-process-creation-to-stealthy-injection/
        https://github.com/MalwareTech/EDR-Preloader
    # 硬件断点
        https://github.com/rad9800/hwbp4mw

混杂
    https://github.com/oldboy21/SWAPPALA
    https://oldboy21.github.io/posts/2024/09/timer-callbacks-spoofing-to-improve-your-sleap-and-swappala-untold/

C/C++开发
    https://github.com/serge1/COFFI
    https://github.com/vxunderground/VX-API/tree/main/VX-API
    https://github.com/0cch/moderncpp_public
    https://www.ired.team/offensive-security/defense-evasion/how-to-unhook-a-dll-using-c++

https://www.incendium.rocks/posts/Automating-MS-RPC-Vulnerability-Research/
```