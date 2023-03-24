
一直想学习下Host碰撞，换了新公司后终于有时间可以学习下

# 0x01 漏洞原理
在当今的反向代理技术架构下，正常访问一个网站的流程是：
用户通过浏览器访问一个域名 -> 先在本地hosts文件中查询域名对应的IP，没查到的话再通过DNS查询域名对应的IP -> 访问查询到的IP并以最初访问的域名作为请求头中host字段的值 -> 反代服务器nginx根据host字段的值转发到对应的server_name下

补充一句：有些网站通过IP不能直接访问就是因为它本身是一个反代服务器，并且在配置文件中配置了不允许通过IP直接访问

nginx配置文件——反代服务器，注释中包含对配置文件的解释：
```
server {
    listen 8080 default_server; # 指定当前为默认server
    
    # host为空时返回400
server_name _; 
    return 400;
}
server {
    listen 8080;
    
# host为test.com时，转发到http://127.0.0.1:80
server_name test.com;
    location {
        proxy_pass http://127.0.0.1:80;
        proxy_redirect off;
        proxy_set_header Host $host:$server_port;
        proxy_set_header X-Real-IP $remote_addr;
        root html;
        index index.html index.htm;
    }
    
access_log logs/test.com.log;
}
```
nginx配置文件——业务
```
server {
    listen 80;
    server_name localhost;
    location {
        root usr/share/nginx/html;
        index index.html index.htm;
    }
    error_page 500 502 503 504 50x.html;
    location = 50x.html {
        root usr/share/nginx/html;
    }
}
```
漏洞就出现在，当目标单位删除了DNS中host对应的IP，但是没有删除反代服务器中host对应的server，此时我们访问反代服务器的IP且host头中带有对应域名，若域名匹配反代服务器的server，则能够访问到内网业务

# 漏洞利用
分析完了漏洞形成的原因，我们知道如果找到域名解析对应的IP，且访问IP时host头带上对应的域名，则可以访问目标单位的内部资产，那如何找到域名解析对应的IP，就需要大量的IP和域名来进行碰撞

参考工具：https://github.com/pmiaowu/HostCollision

# 参考链接
团队内部分享：WEB非实用之host碰撞挖掘  
https://www.modb.pro/db/136373  