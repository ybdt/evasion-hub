# 0x01 Nim简介
Nim原名Nimrod，是一种静态类型的、编译型的语言，本质上是一个翻译型语言，所以可以编译为C、C++、Object-C、JavaScript，语法类似Python

# 0x02 Nim安装
## 01 *nix下安装
### 方式1：通过sh脚本
```
curl https://nim-lang.org/choosenim/init.sh -sSf | sh
```
### 方式2：下载编译好的二进制
```
https://nim-lang.org/download/nim-1.6.12-linux_x64.tar.xz
https://nim-lang.org/download/nim-1.6.12-linux_x32.tar.xz
```
### 方式3：下载源代码自己编译
```
https://nim-lang.org/download/nim-1.6.12.tar.xz

sh build.sh
bin/nim c koch
./koch boot -d:release
./koch tools
```
### 方式4：通过包管理器
```
# debian/ubuntu
apt install nim

# macOS
brew install nim

# 其他系统如Docker、Arch Linux、FreeBSD、OpenBSD、openSUSE、Void Linux参见：
https://nim-lang.org/install_unix.html
```
### 配置环境变量

对于编译好的二进制，配置如下环境变量

```
bin directory
~/.nimble/bin (where ~ is the home directory)
```
### 编译器依赖
Nim依赖C编译器，因此必须安装它并确保它在PATH环境变量中
```
# MacOS下安装clang
xcode-select --install

# Linux下通常默认带有C编译器，或者通过包管理器安装gcc或clang
```
### 

我这里选择包管理器的方式去安装，并安装Nim依赖的C编译器

```
brew install nim
xcode-select --install
```

## 02 Windows下安装

### 方式1：手动安装配置
```
下载并解压：https://nim-lang.org/download/nim-1.6.12_x64.zip

解压后配置PATH环境变量
bin directory
~/.nimble/bin (where ~ is the home directory)

如果没安装mingw还需要手动安装mingw
```
### 方式2：自动安装配置
```
下载并解压：https://nim-lang.org/download/nim-1.6.12_x64.zip

解压后，执行里面的finish.exe，他会自动做2件事，配置PATH环境变量以及安装mingw
```
### 方式3：通过choosenim



我这里选择自动安装配置的方式，下载解压后，执行finish.exe，下载mingw后为它配置一下环境变量

# 0x03 Nim基本语法
nim的官方文档挺有趣的，会分为2类，对于有编程基础的建议看5分钟快速指南，对于没有编程基础的建议看详细指南，以下学习基于5分钟快速指南：https://learnxinyminutes.com/docs/nim/

## 01 注释
单行注释使用#
多行注释使`#[`和`]#`，且多行注释可以内嵌
```
# Single-line comments start with a #

#[
  This is a multiline comment.
  In Nim, multiline comments can be nested, beginning with #[
  ... and ending with ]#
]#
```
多行注释还可以使用discard """
```
discard """
This can also work as a multiline comment.
Or for unparsable, broken code
"""
```

## 02 变量声明
使用var声明变量

可在声明的同时进行初始化，也可只声明不初始化

可带有类型，也可不带有类型

```
var
  boat: float
  letter: char = 'n'
  nLength: int = len(lang)
  truth: bool = false
  lang = "N" & "im"
```

使用let声明的变量是不可变的
```
let
  legs = 400
  aboutPi = 3.15
  arms = 2_000  # _ are ignored and are useful for long numbers.
```

使用const声明的常量是在编译时使用，这提供更好的性能，且对编译时表达式很有用
```
const
  debug = true
  compileBadCode = false
```

when类似于编译时if，就是说compileBadCode为false时，下列语句不会被编译
```
when compileBadCode:
  legs = legs + 1
  const input = readline(stdin)  # 注意const类型的值在编译时必须是已知的，也就是说，这条语句是不行的
```

如果一个表达式的结果未使用，编译器会提醒，可通过如下指令屏蔽提醒
```
discard 1 > 2
```

# 0x04 输入输出和流程控制

case：类似于C语言中的case
readLine()：从标准输入或文件读入

```
echo "Read any good books lately?"
case readLine(stdin)
of "no", "No":
  echo "Go to your local library."
of "yes", "Yes":
  echo "Carry on, then."
else:
  echo "That's great; I assume."
```

while, if, continue, break：类似于C语言中的while, if, continue, break

```
import strutils as str # http://nim-lang.org/docs/strutils.html
echo "I'm thinking of a number between 41 and 43. Guess which!"
let number: int = 42
var
  raw_guess: string
  guess: int
while guess != number:
  raw_guess = readLine(stdin)
  if raw_guess == "": continue # Skip this iteration
  guess = str.parseInt(raw_guess)
  if guess == 1001:
    echo("AAAAAAGGG!")
    break
  elif guess > number:
    echo("Nope. Too high.")
  elif guess < number:
    echo(guess, " is too low")
  else:
    echo("Yeeeeeehaw!")
```
Iteration：循环
```
for i, elem in ["Yes", "No", "Maybe so"]: # Or just `for elem in`
  echo(elem, " is at index: ", i)

for k, v in items(@[(person: "You", power: 100), (person: "Me", power: 9000)]):
  echo v

let myString = """
an <example>
`string` to
play with
""" # Multiline raw string

for line in splitLines(myString):
  echo(line)

for i, c in myString:       # Index and letter. Or `for j in` for just letter
  if i mod 2 == 0: continue # Compact `if` form
  elif c == 'X': break
  else: echo(c)
```