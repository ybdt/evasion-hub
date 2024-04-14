当下，权限维持好用的方式：1、白加黑，2、syscall方式注入shellcode

# 0x01 白加黑权限维持
### 漏洞原理
这是一个很古老，但仍旧很有效的方式，原理很简单
```
某些exe需要加载dll，而dll查找顺序如下
01 exe所在目录
02 系统⽬录即System32⽬录
03 16位系统⽬录即System⽬录（用户兼容16位应用，可以不考虑）
04 Windows目录
05 加载dll时所在的当前目录
06 环境变量path中的所有目录
所以，当一个dll不在应用程序所在目录，那么我们就可以在应用程序所在目录放一个自己dll，名字改为要加载的dll名称，当程序启动时，便会加载我们的dll
```
更深入的漏洞原理
```
DLL劫持漏洞之所以被称为漏洞，还要从负责加载DLL的系统API LoadLibrary来看。熟悉Windows代码的同学都知道，调⽤LoadLibrary时可以使⽤DLL的相对路径。这时，系统会按照特定的顺序搜索⼀些⽬录，以确定DLL的完整路径。根据MSDN⽂档的约定，在使⽤相对路径调⽤LoadLibrary（同样适⽤于其他同类LoadLibraryEx）时，系统会依次从以下6个位置去查找所需要的DLL⽂件（会根据SafeDllSearchMode配置⽽稍有不同）

程序所在⽬录
加载dll时所在的当前⽬录
系统⽬录即System32⽬录
16位系统⽬录即System⽬录
Windows⽬录
Path环境变量中列出的⽬录
```
### dll劫持防御1
微软从Win7开始，为了防御系统dll被劫持，将经常被劫持的系统dll写进一个注册表项中，此注册表项中的dll只能被System32目录下的exe调用，不能从exe所在的当前目录调用，注册表路径如下
```
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\KnownDLLs

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\ExcludeFromKnownDlls
```
### dll劫持防御2
目前不少厂商已经通过哈希校验、数字签名校验等方式，确保加载的dll为自己的dll，这样即便找到了可劫持dll的白利用，仍然无法劫持
### dll劫持场景1
有些开发者编写程序时，没有对程序加载的dll做处理，导致加载一些不存在的dll，这个时候我们可以劫持这些不存在的dll
### dll劫持场景2
利用加载顺序，exe所在目录先于系统目录System32，劫持系统dll