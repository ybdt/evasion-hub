# Attention
```
当前项目子目录中的代码均为测试过可成功编译且功能正常

The code in the current project subdirectory has all been tested and found to be successfully compilable and functioning properly.
```

# 01-DLL-Hijacking
```
# has read
【HijackLibs】https://hijacklibs.net/
【DLL Sideloading for Initial Access – Red Team Operator's Guide】https://print3m.github.io/blog/dll-sideloading-for-initial-access

# to read
https://www.r-tec.net/r-tec-blog-dll-sideloading.html
```

# 02-Function-Address-Locate
```
# has read
https://github.com/LloydLabs/Windows-API-Hashing/

# to read
https://github.com/Teach2Breach/stargate/blob/main/blog.md
https://mp.weixin.qq.com/s/O4LCnC_DjzfvnLvgXm1bFQ
```

# 03-Sandbox-Evasion
```
# to read
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
# to read
https://github.com/EvilBytecode/Ebyte-AMSI-ProxyInjector
https://www.r-tec.net/r-tec-blog-bypass-amsi-in-2025.html
```

# 05-Allocate-Write-Execute
```
# has read
【Thread Name-Calling – using Thread Name for offense】https://research.checkpoint.com/2024/thread-name-calling-using-thread-name-for-offense/

# to read
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
# has read
【深入理解 Windows 进程属性：从 PPID 欺骗到句柄继承】https://mp.weixin.qq.com/s/-0MbfIWFnpUD2P4IZRBrkQ

# to read
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
# to read
https://www.blackhillsinfosec.com/avoiding-memory-scanners/
https://github.com/mgeeky/ShellcodeFluctuation
```

# 08-Code-Obfuscation
```
# to read
【Themida】https://www.oreans.com/Themida.php
【VMProtect】https://vmpsoft.com/
https://github.com/KomiMoe/Arkari
https://github.com/obfuscator-llvm/obfuscator
https://github.com/rasta-mouse/ThreatCheck
https://github.com/dobin/avred
```

# 09-EDR-Blindness
```
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
# to read
https://github.com/hackerhouse-opensource/iscsicpl_bypassUAC
https://www.elastic.co/security-labs/exploring-windows-uac-bypasses-techniques-and-detection-strategies
https://github.com/zer0antisec/UACBypass/tree/main
```

# 11-Privilege-Escalation
```
# to read
https://www.mdsec.co.uk/2026/02/total-recall-retracing-your-steps-back-to-nt-authoritysystem/
```

# 12-Persistence
```
# has read
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
# to read
https://github.com/cube0x0/MiniDump
```

# 14-Evasion-With-LLM
```
# to read
https://mp.weixin.qq.com/s/VVmDDPcChtWF_yA-zv47zQ?click_id=1
https://www.outflank.nl/blog/2025/08/07/training-specialist-models/
```

# Misc
```
【揭露天鹅向量（Swan Vector）APT组织：针对中国台湾和日本的多阶段DLL植入攻击】https://mp.weixin.qq.com/s/ZUR7-2OdZcQiq8A8qiptwg
【Operation(润)RUN：“离岸爱国者”的赛博狂欢】https://mp.weixin.qq.com/s/S7Iq5DfO7xNX3GPJzwedPw
【CVE-2025-33053, Stealth Falcon and Horus: A Saga of Middle Eastern Cyber Espionage】https://research.checkpoint.com/2025/stealth-falcon-zero-day/
【阻断EDR Agent和Server端交流】https://cloudbrothers.info/en/edr-silencers-exploring-methods-block-edr-communication-part-1/
【WinDBG使用】https://p.ost2.fyi/
【逆向工程】https://github.com/DebugPrivilege/InsightEngineering
【内核调试1】https://www.youtube.com/watch?v=K5abwBNb76k&list=PLUFkSN0XLZ-ka9dfeHWmhqDV-qIns-9uR
【内核调试2】https://www.youtube.com/watch?v=_5c8ErwyqiU&list=PLUFkSN0XLZ-kOQnYJwx3x9wPMDjlv2iSg
【内核调试3】https://www.youtube.com/watch?v=SSerGWQW70c&list=PLUFkSN0XLZ-nl4HEX4_LWG9H_d9vJKkYL
```