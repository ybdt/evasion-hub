# 0x00 项目前言
项目缘起：总能看到有人分享各种字典，拿到字典后又发现很多重复的东西，手动去重太麻烦了，想到写一个字典去重工具，想法越来越多，故有此项目

# 0x01 项目宗旨
本项目旨在记录我在渗透测试中用到的有效字典，对于相关的优秀项目，我并不会将字典全部收集到这里，而是列到文末

# 0x02 dict-cleaner.py
功能：可对指定文件（如dict.txt）去重，或将新字典添加到旧字典尾部后对旧字典去重，生成去重后的新文件（新文件名dict-new.txt）

2020/12/30-发现有些字典的换行符是"\n"，有些字典的换行符是"\r\n"  
新增功能：对linux和windows下换行符做适配

2020/12/30-发现有些字典的每行首尾包含空格或制表符  
新增功能：去重的同时会去除每行首尾的空格符(" ")、回车符("\r")、换行符("\n")、制表符("\t")

2020/12/31-发现有些字典的默认字符集不是UTF-8  
新增功能：先识别目标字典的字符集，再用指定字符集打开字典

# 0x03 项目记录
字典将按照“服务”分类，每个“服务”下包含各种fuzz字典  
新字典添加到本项目前，会进行去重、去除每行首尾的空格





### 厂商设备：
[https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/](https://lionking.top/2019/09/15/%E5%90%84%E5%A4%A7%E5%8E%82%E5%95%86%E8%AE%BE%E5%A4%87%E9%BB%98%E8%AE%A4%E5%AF%86%E7%A0%81/)收录到“厂商设备/readme.md”

### 数字相关字典：
4-digital-dict.txt：4位数字字典  
6-digital-dict.txt：6位数字字典

# 0x04 优秀项目
https://github.com/rootphantomer/Blasting_dictionary  
https://weakpass.com/  
https://github.com/3had0w/Fuzzing-Dicts  
https://github.com/TheKingOfDuck/fuzzDicts  
https://github.com/danielmiessler/SecLists  
https://github.com/epony4c/Exploit-Dictionary  
https://github.com/c0ny1/upload-fuzz-dic-builder  
https://github.com/gh0stkey/Web-Fuzzing-Box  
默认凭证字典：https://github.com/ihebski/DefaultCreds-cheat-sheet
