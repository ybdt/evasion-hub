## 如何实现自己的自动化资产收集工具
基本思路：目标单位根域名及100%控股子公司根域名 -> 子域名 -> ip全端口 -> 连续ip -> web爬虫及web路径

### 根域名
可调用[enscan](https://github.com/wgpsec/ENScan_GO)自动化收集“目标单位根域名及100%控股子公司根域名”
### 子域名
子域名的收集分两个方向：通过各类接口（如：fofa）或爆破子域名，我这边是用python实现调用fofa、hunter、quake，后测试发现quake比较坑，就把quake去掉了，再后来将oneforall加进来，oneforall包含了大量接口（需要配置好api）以及自带masscan爆破子域名，此时通过接口收集以及通过爆破收集，我们都用到了
### ip全端口
对于收集到的子域名，通过ping解析出对应ip，并判断出是否是cdn节点（云waf节点），判断方法是对比ping后返回的域名和最初的域名是否一致，如
```
ping www.baidu.com
返回
PING www.a.shifen.com (39.156.66.14): 56 data bytes
```
不过执行时会发现这样太慢，所以你又会用到多线程、队列，至此，得到非cdn节点（云waf节点）的ip后
### 连续ip
得到非cdn节点（云waf节点）的ip后，如1.1.1.1，1.1.1.3，1.1.1.5，那往往1.1.1.2，1.1.1.4也属于目标，所以我们要通过一个算法实现获取连续ip，这个算法在几个知识星球发过，这里也发一下
```
# 获取连续IP，例如：公网IP 202.48.45.46、202.48.45.78、202.48.45.108，会获取其中间隔的全部IP
def ipSerial(ip_list):
    # ip地址会出现ipv6的情况，所以需要处理一下
    legal_ip_list = []
    for ip in ip_list:
        if len(ip.split(".")) != 4:
            continue
        else:
            legal_ip_list.append(ip)

    d = {}
    for ip in legal_ip_list:
        ip_parts = ip.split(".")
        c_range = ip_parts[0] + "." + ip_parts[1] + "." + ip_parts[2]
        if c_range not in d.keys():
            c_range_elements = []
            d[c_range] = c_range_elements
            c_range_elements.append(ip)
        else:
            c_range_elements = d[c_range]
            c_range_elements.append(ip)
    print()
    print("非CDN IP按C段分类：" + str(d))

    serial_ip_list = []
    for key, value_list in d.items():
        if len(value_list) == 1:
            # print(value_list[0])
            serial_ip_list.append(value_list[0])
        else:
            # print(value_list)
            ip_parts = value_list[0].split(".")
            c_range = ip_parts[0] + "." + ip_parts[1] + "." + ip_parts[2]
            ip_last_part_list = []
            for ip_addr in value_list:
                ip_last_part_list.append(int(ip_addr.split(".")[3]))
            ip_last_part_list.sort()
            # print(ip_last_part_list)  # debug code
            # print(ip_last_part_list[0])  # debug code
            start = int(ip_last_part_list[0])
            end = int(ip_last_part_list[-1])
            for i in range(start, end + 1):
                new_ip = c_range + "." + str(i)
                # print(new_ip)
                serial_ip_list.append(new_ip)
    # print(serial_ip_list)  # debug code

    return serial_ip_list
```
此时收集到相对较全的ip，对每个ip查询全端口，这里调用nmap查询全端口会比较慢，可以先调用空间测绘查询ip全端口，最后将端口和ip结合，重新构造url
### web爬虫及web路径
最后，对每个url进行网站爬取及web路径爆破，网站爬取推荐[crawlergo](https://github.com/Qianlitp/crawlergo)，web路径爆破推荐[dirsearch](https://github.com/maurosoria/dirsearch)

### 通过python，将上述过程实现自动化，就是一个自动化资产收集工具