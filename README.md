项目缘起：总能看到有人分享各种字典，拿到字典后又发现很多重复的东西，手动去重太麻烦了，想到写一个字典去重工具，想法越来越多，进而有了此项目

# 0x00 项目介绍
本项目将字典按照服务分类，每个服务下包含用户名fuzz字典、口令fuzz字典、默认口令fuzz字典中的一种或几种

# 0x01 项目记录
#### SSH：  
[https://weakpass.com/](https://weakpass.com/)中的online_brute收录到ssh-pass-fuzz-top52.txt

### Tomcat：  
[https://github.com/magicming200/tomcat-weak-password-scanner](https://github.com/magicming200/tomcat-weak-password-scanner)中的username.txt和password.txt收录到tomcat-user:pass-fuzz-top424.txt

### WEB：  
[https://download.csdn.net/download/ljp123123ljp/9145013](https://download.csdn.net/download/ljp123123ljp/9145013)收录到web-user-fuzz-top605-for-chinese.txt  
渗透测试中收集到的姓名收录到web-user-fuzz-top605-for-chinese.txt  
[https://www.iteye.com/resource/h4ck1y-10653176](https://www.iteye.com/resource/h4ck1y-10653176)收录到web-pass-fuzz-top1002.txt  
渗透测试中收集到的口令收录到web-pass-fuzz-top1002.txt

### WebLogic：  
[https://github.com/rootphantomer/Blasting_dictionary](https://github.com/rootphantomer/Blasting_dictionary)中的weblogic默认密码列表.txt收录到weblogic-default-user:pass-fuzz-top8.txt

### 厂商设备：  
[https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/](https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/)收录到readme.md

### 字典去重：  
dict-cleaner.py->字典去重工具  
dict-cleaned.txt->去重后的字典

### 数字：  
4-digital-dict.txt->4位数字字典  
6-digital-dict.txt->6位数字字典  
digital-dict-generator.py->数字字典生成器
