# 0x01-项目起源
红队Web打点中，发现口令问题占比不小，遂创建此项目

# 0x02-字典来源
棱角安全团队整理的默认凭证  https://forum.ywhack.com/bountytips.php?password  
ihebski整理的默认凭证  https://github.com/ihebski/DefaultCreds-cheat-sheet  

鸭王师傅  https://github.com/TheKingOfDuck/fuzzDicts  
3hadow师傅  https://github.com/3had0w/Fuzzing-Dicts  
c0ny1师傅  https://github.com/c0ny1/upload-fuzz-dic-builder  
gh0stkey师傅  https://github.com/gh0stkey/Web-Fuzzing-Box  
gh0stkey师傅  https://gh0st.cn/archives/2019-11-11/1  
https://github.com/huyuanzhi2/password_brute_dictionary  
https://github.com/danielmiessler/SecLists  
https://weakpass.com/  
https://github.com/mstxq17/SeCDictionary/  
https://nordpass.com/most-common-passwords-list/  
https://pastebin.com/LMuD0LGa  


# 0x03-思路说明
借助python实现一款自动化检测Web账户口令的工具，将“有错误次数限制”、“有验证码”、“有前端加密”的url挑选出来，单独存到一个文件，其余情况自动化测试