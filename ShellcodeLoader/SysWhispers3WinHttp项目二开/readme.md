原项目地址：https://github.com/huaigu4ng/SysWhispers3WinHttp

项目原理：  
01 借助winhttp库从指定的URL下载shellcode到内存  
02 以SysWhispers3的方式执行shellcode

二开改进的地方：  
改进1：添加启动密码来反沙箱  
改进2：从http改为https，防止基于流量的检测  
改进3：从个人vps改为公共服务，防止对个人vps标黑