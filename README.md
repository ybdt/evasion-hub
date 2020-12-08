项目缘起：总能看到有人分享各种字典，拿到字典后又发现很多重复的东西，手动去重太麻烦了，想到写一个字典去重工具，想法越来越多，进而有了此项目

# 0x00 项目介绍
本项目将字典按照服务分类，每个服务下包含用户名fuzz字典、口令fuzz字典、默认口令fuzz字典中的一种或几种

# 0x01 工具介绍
v0.1  
功能介绍：读取一个字典文件，去重，合并到ybdt-full-dict.txt中

v0.2  
功能改善：改善大文件的读取方式（当读取23.5MB的字典文件时，cpu占用非常高，程序跑的也很慢）  
功能添加：对不同换行结尾的字典文件同时兼容（linux下创建的文件默认以\n结尾，windows下创建的文件默认以\r\n结尾）

# 0x02 项目记录
SSH:  
!(https://weakpass.com/)[https://weakpass.com/]中的online_brute收录到ssh-pass-fuzz-top52.txt

WebLogic:  
!(https://github.com/rootphantomer/Blasting_dictionary)[https://github.com/rootphantomer/Blasting_dictionary]中的weblogic默认密码列表.txt收录到weblogic-default-user:pass-fuzz-top8.txt

Tomcat:  
!(https://github.com/magicming200/tomcat-weak-password-scanner)[https://github.com/magicming200/tomcat-weak-password-scanner]中的username.txt和password.txt收录到tomcat-user:pass-fuzz-top424.txt

WEB:  
!(https://download.csdn.net/download/ljp123123ljp/9145013)[https://download.csdn.net/download/ljp123123ljp/9145013]收录到web-user-fuzz-top605-for-chinese.txt  
渗透测试中收集到的姓名收录到web-user-fuzz-top605-for-chinese.txt  
!(https://www.iteye.com/resource/h4ck1y-10653176)[https://www.iteye.com/resource/h4ck1y-10653176]收录到web-pass-fuzz-top1002.txt  
渗透测试中收集到的口令收录到web-pass-fuzz-top1002.txt

厂商设备：  
!(https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/)[https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/]收录到readme.md
