The code in current project has been tested compile successfully and function properly.

# 01-DLL-Hijacking
```
【HijackLibs】https://hijacklibs.net/
【DLL Sideloading for Initial Access – Red Team Operator's Guide】https://print3m.github.io/blog/dll-sideloading-for-initial-access
【DLL Sideloading】https://www.r-tec.net/r-tec-blog-dll-sideloading.html
```

# 02-Function-Address-Locate
```
【Windows-API-Hashing】https://github.com/LloydLabs/Windows-API-Hashing/
【Windows安全攻防-PEB&TEB】https://mp.weixin.qq.com/s/RTyafWl13djCI5ua6LFQ6w
【Stargate: Bypassing EDR Hooks Through Signature-Based Function Discovery】https://github.com/Teach2Breach/stargate/blob/main/blog.md
【答应我，别在shellcode中通过遍历PEB获取模块基址了好么？】https://mp.weixin.qq.com/s/O4LCnC_DjzfvnLvgXm1bFQ
```

# 03-Sandbox-Evasion
```
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
```

# 04-AMSI-and-ETW-Bypass
```
https://github.com/EvilBytecode/Ebyte-AMSI-ProxyInjector
https://www.r-tec.net/r-tec-blog-bypass-amsi-in-2025.html
```

# 05-Allocate-Write-Execute
```
【Thread Name-Calling – using Thread Name for offense】https://research.checkpoint.com/2024/thread-name-calling-using-thread-name-for-offense/
【绕过 Elatic EDR 用户态 Hook：从原理到实战】https://mp.weixin.qq.com/s/ghG4d9ebz2fccAOf6sawEQ?scene=1
https://research.checkpoint.com/2025/waiting-thread-hijacking/
https://github.com/thomasxm/BOAZ_beta
https://blog.malicious.group/writing-your-own-rdi-srdi-loader-using-c-and-asm/
https://github.com/Friends-Security/RedirectThread
https://github.com/NUL0x4C/AtomLdr
https://github.com/kyleavery/AceLdr
https://github.com/oldboy21/SWAPPALA
https://oldboy21.github.io/posts/2024/09/timer-callbacks-spoofing-to-improve-your-sleap-and-swappala-untold/
```

# 06-Remote-Inject
```
【深入理解 Windows 进程属性：从 PPID 欺骗到句柄继承】https://mp.weixin.qq.com/s/-0MbfIWFnpUD2P4IZRBrkQ
https://repnz.github.io/posts/apc/user-apc/
https://repnz.github.io/posts/apc/kernel-user-apc-api/
https://repnz.github.io/posts/apc/wow64-user-apc/
https://github.com/repnz/apc-research
https://bruteratel.com/research/2024/10/20/Exception-Junction/
https://github.com/passthehashbrowns/VectoredExceptionHandling
https://www.malwaretech.com/2024/02/bypassing-edrs-with-edr-preload.html
https://www.outflank.nl/blog/2024/10/15/introducing-early-cascade-injection-from-windows-process-creation-to-stealthy-injection/
https://github.com/MalwareTech/EDR-Preloader
https://github.com/rad9800/hwbp4mw
```

# 07-Sleep-Mask
```
【绕过杀软EDR内存扫描】https://mp.weixin.qq.com/s/ep376tna5lZX50eu5oLMfA?scene=1
【Avoiding Memory Scanners】https://www.blackhillsinfosec.com/avoiding-memory-scanners/
https://github.com/mgeeky/ShellcodeFluctuation
```

# 08-Code-Obfuscation
```
https://www.oreans.com/Themida.php
https://vmpsoft.com/
https://github.com/KomiMoe/Arkari
https://github.com/obfuscator-llvm/obfuscator
https://github.com/rasta-mouse/ThreatCheck
https://github.com/dobin/avred
```


# 09-EDR-Blindness
```
【"银狐"新进展：多Rootkit配合，内核InfinityHook+穿透读写】https://mp.weixin.qq.com/s/yzEuztYDbiSv0YrN2My_Ow?scene=1
【持续演进的银狐——不断增加脆弱驱动通过BYOVD结束防病毒软件】https://mp.weixin.qq.com/s/S_y9pfiqgcMV9wusELOfBw?scene=1
【利用AppLocker策略关闭EDR】https://mp.weixin.qq.com/s/qMW0Ct4e8zpL6sUghEc7Hg?scene=1
【【安全研究】使用内核驱动程序来隐藏和终止进程】https://mp.weixin.qq.com/s/IBZITOzGJYMVo4Be7_pb7Q?scene=1
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
https://www.loldrivers.io/
https://github.com/m0nad/Diamorphine
https://github.com/bytecode77/r77-rootkit
https://github.com/eversinc33/Banshee
https://myzxcg.com/2023/09/白驱动-Kill-AV/EDR上/
https://xz.aliyun.com/news/12373
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
```

# 10-UAC-Bypass
```
https://github.com/hackerhouse-opensource/iscsicpl_bypassUAC
https://www.elastic.co/security-labs/exploring-windows-uac-bypasses-techniques-and-detection-strategies
https://github.com/zer0antisec/UACBypass/tree/main
```

# 11-Privilege-Escalation
```
https://www.mdsec.co.uk/2026/02/total-recall-retracing-your-steps-back-to-nt-authoritysystem/
```

# 12-Persistence
```
https://mohamed-fakroud.gitbook.io/red-teamings-dojo/windows-internals/playing-around-com-objects-part-1
https://googleprojectzero.blogspot.com/2025/01/windows-bug-class-accessing-trapped-com.html
https://mohamed-fakroud.gitbook.io/red-teamings-dojo/abusing-idispatch-for-trapped-com-object-access-and-injecting-into-ppl-processes
https://bohops.com/2018/06/28/abusing-com-registry-structure-clsid-localserver32-inprocserver32/
https://bohops.com/2018/08/18/abusing-the-com-registry-structure-part-2-loading-techniques-for-evasion-and-persistence/
https://bohops.com/2018/03/17/abusing-exported-functions-and-exposed-dcom-interfaces-for-pass-thru-command-execution-and-lateral-movement/
https://www.ibm.com/think/x-force/remotemonologue-weaponizing-dcom-ntlm-authentication-coercions
https://www.ibm.com/think/news/fileless-lateral-movement-trapped-com-objects
https://medium.com/@andreabocchetti88/living-off-the-com-type-coercion-abuse-108f988bb00a
```

# 13-Credential-Dump
```
https://github.com/dazzyddos/lsawhisper-bof
https://github.com/EvanMcBroom/lsa-whisperer
https://github.com/cube0x0/MiniDump
```

# 14-Evasion-With-LLM
```
【还在手搓免杀？时代变了】https://mp.weixin.qq.com/s/VVmDDPcChtWF_yA-zv47zQ?click_id=1
【Training Specialist Models: Automating Malware Development】https://www.outflank.nl/blog/2025/08/07/training-specialist-models/
```

# Misc
```
【x64汇编与shellcode入门教程 01】https://mp.weixin.qq.com/s/HzEWKEpYpeBNJyk4IEll2g?scene=1
【x64汇编与shellcode入门教程 02】https://mp.weixin.qq.com/s/vEfsmgBpEOJSzvXcvnEtUA?scene=1
【x64汇编与shellcode入门教程 03】https://mp.weixin.qq.com/s/bJnqwt0_9rQCmaYZFrcFKg?scene=1
【x64汇编与shellcode入门教程 04】https://mp.weixin.qq.com/s/-SEK85Fflt-Gr_Km9YcD3w?scene=1
【x64汇编与shellcode入门教程 05】https://mp.weixin.qq.com/s/xC02bij37DTr_j4arJi_ag?scene=1
【x64汇编与shellcode入门教程 06】https://mp.weixin.qq.com/s/db2pQXBx44IF4Dst0hw9sQ?scene=1
【x64汇编与shellcode入门教程 07】https://mp.weixin.qq.com/s/AmjTv9wzFqzV1GKZYUecNQ
【OpenSecurityTraining2】https://p.ost2.fyi/
【Debuggers 3011, Advanced WinDbg】https://www.youtube.com/watch?v=K5abwBNb76k&list=PLUFkSN0XLZ-ka9dfeHWmhqDV-qIns-9uR
【Architecture 2821, Windows Kernel Internels 2】https://www.youtube.com/watch?v=_5c8ErwyqiU&list=PLUFkSN0XLZ-kOQnYJwx3x9wPMDjlv2iSg
【Exploitation 4011, Windows Kernel Exploitation: Race Condition + UAF in KTM】https://www.youtube.com/watch?v=SSerGWQW70c&list=PLUFkSN0XLZ-nl4HEX4_LWG9H_d9vJKkYL
```