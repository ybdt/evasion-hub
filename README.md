# 0x00 项目介绍
首先：本项目针对的是渗透测试中的弱口令，既然项目定义是弱口令，就不会上不封顶的无限融合各种字典，暂定弱口令数量为10000  
其次：另外针对不同服务的弱口令习惯是不一样的，比如web服务的弱口令人们首先想到admin、admin888等，而ssh服务的弱口令人们首先想到Passw0rd等，所以弱口令要分类

# 0x01 工具介绍
开发说明：ybdt-dict-cleaner.py是在ubuntu18.04下开发，在ubuntu18.04下使用没有问题  
功能介绍：读取一个字典文件，去重，合并到ybdt-dict-web.txt中

# 0x02 字典介绍
ybdt-dict-web.txt收集的字典包括：  
https://github.com/insightglacier/Dictionary-Of-Pentesting/tree/master/Generalpassword 中的全部字典  
https://github.com/honorxux/Fuzz-Dicts/tree/master/%E5%AF%86%E7%A0%81%E5%AD%97%E5%85%B8 中的1000常用密码字典.txt和6000常用密码字典.txt
