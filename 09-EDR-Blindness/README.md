# Excellent-Article-Project
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