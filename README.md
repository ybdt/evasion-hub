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

# 0x02 字典介绍
https://github.com/insightglacier/Dictionary-Of-Pentesting/tree/master/Generalpassword 中的全部字典 收集到 ybdt-full-dict.txt  
https://github.com/honorxux/Fuzz-Dicts/tree/master/%E5%AF%86%E7%A0%81%E5%AD%97%E5%85%B8 中的1000常用密码字典.txt和6000常用密码字典.txt 收集到 ybdt-full-dict.txt  
https://weakpass.com/ 中的online_brute 收集到 各种服务常见弱口令/ssh-weak-pass.txt  
https://github.com/rootphantomer/Blasting_dictionary 中的weblogic默认密码列表.txt 收集到 各种服务默认口令/weblogic-default-passwd.txt  
https://github.com/droope/pwlist 中saved/saved1.txt 收集到 ybdt-full-dict.txt

# 0x03 贡献介绍
欢迎各位师傅提交issue，我会将被收录的字典贡献者列在下方
