项目缘起：总能看到有人分享各种字典，拿到字典后又发现很多重复的东西，手动去重太麻烦了，想到写一个字典去重工具，想法越来越多，进而有了此项目

# 0x00 项目介绍
本项目将字典按照服务分类，各个服务下有对应的常见弱口令、默认口令等  
ybdt-full-dict.txt：是没有按照服务分类，只是对网上收集到的字典进行汇总  

# 0x01 工具介绍
v0.1  
功能介绍：读取一个字典文件，去重，合并到ybdt-full-dict.txt中

v0.2  
功能改善：改善大文件的读取方式（当读取23.5MB的字典文件时，cpu占用非常高，程序跑的也很慢）  
功能添加：对不同换行结尾的字典文件同时兼容（linux下创建的文件默认以\n结尾，windows下创建的文件默认以\r\n结尾）

# 0x02 字典记录
ybdt-full-dict.txt：  
https://github.com/insightglacier/Dictionary-Of-Pentesting/tree/master/Generalpassword 中的全部字典  
https://github.com/honorxux/Fuzz-Dicts/tree/master/%E5%AF%86%E7%A0%81%E5%AD%97%E5%85%B8 中的1000常用密码字典.txt和6000常用密码字典.txt  
https://github.com/droope/pwlist 中saved/saved1.txt  
SSH:  
https://weakpass.com/ 中的online_brute收录到-》ssh-weak-pass-top52.txt  
WebLogic:  
https://github.com/rootphantomer/Blasting_dictionary 中的weblogic默认密码列表.txt收录到-》weblogic-default-passwd.txt  
Tomcat：  
https://github.com/magicming200/tomcat-weak-password-scanner 中的username.txt和password.txt收录到-》tomcat-weak-pass-top424.txt  
WEB:  
https://download.csdn.net/download/ljp123123ljp/9145013 收录到-》常见中国姓名top605.txt  
平时渗透测试收集的常见姓名收录到-》常见中国姓名top605.txt  
https://www.iteye.com/resource/h4ck1y-10653176 收录到-》web-weak-pass-top1002.txt  
平时渗透测试收集的口令收录到-》web-weak-pass-top1002.txt

# 0x03 贡献介绍
欢迎各位师傅提交issue，我会将被收录的字典贡献者列在下方
