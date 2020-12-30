# 0x00 前言
项目缘起：总能看到有人分享各种字典，拿到字典后又发现很多重复的东西，手动去重太麻烦了，想到写一个字典去重工具，想法越来越多，进而有了此项目

# 0x01 项目介绍
本项目将字典按照“服务”分类，每个“服务”下包含各种fuzz字典

# 0x02 项目记录
dict-cleaner.py：字典去重工具  
dict-cleaned.txt：去重后的字典

### SSH：
[https://weakpass.com/](https://weakpass.com/)中的“online_brute”收录到“SSH/ssh-pass-fuzz-top52.txt”

### Tomcat：
[https://github.com/magicming200/tomcat-weak-password-scanner](https://github.com/magicming200/tomcat-weak-password-scanner)中的“username.txt”和“password.txt”收录到“Tomcat/tomcat-user:pass-fuzz-top424.txt”  
generate-tomcat-user:pass.py：读取user.txt和pass.txt并生成符合tomcat验证时的格式user:pass

### WEB（最后更新时间2020/12/30）：
[https://download.csdn.net/download/ljp123123ljp/9145013](https://download.csdn.net/download/ljp123123ljp/9145013)收录到“WEB/中国人姓名-fuzz-top605.txt”  
+  
[https://www.iteye.com/resource/h4ck1y-10653176](https://www.iteye.com/resource/h4ck1y-10653176)收录到“WEB/网站后台密码-fuzz-top1002.txt”  
+  
[https://github.com/3had0w/Fuzzing-Dicts](https://github.com/3had0w/Fuzzing-Dicts)中的“常见网站备份文件字典（2954）.txt”收录到“WEB/网站备份目录文件-fuzz-top2962.txt”  
+  
平时渗透中收集的信息

### WebLogic：
[https://github.com/rootphantomer/Blasting_dictionary](https://github.com/rootphantomer/Blasting_dictionary)中的“weblogic默认密码列表.txt”收录到“WebLogic/weblogic-default-user:pass-fuzz-top8.txt”

### 厂商设备：
[https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/](https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/)收录到“厂商设备/readme.md”

### 数字相关字典：
4-digital-dict.txt：4位数字字典  
6-digital-dict.txt：6位数字字典  
digital-dict-generator.py：数字字典生成器

# 0x03 其他字典项目
https://github.com/3had0w/Fuzzing-Dicts  
https://github.com/TheKingOfDuck/fuzzDicts
