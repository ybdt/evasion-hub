# 数据结构
Tuples：元组类型，类似于python中的字典
```
var
  child: tuple[name: string, age: int]   # Tuples have *both* field names
  today: tuple[sun: string, temp: float] # *and* order.

child = (name: "Rudiger", age: 2) # Assign all at once with literal ()
today.sun = "Overcast"            # or individual fields.
today.temp = 70.1
```

Sequences：序列类型，类似于python中的列表
```
var
  drinks: seq[string]

drinks = @["Water", "Juice", "Chocolate"] # @[V1,..,Vn] is the sequence literal

drinks.add("Milk")

if "Milk" in drinks:
  echo "We have Milk and ", drinks.len - 1, " other drinks"

let myDrink = drinks[2]
```

自定义类型，类似于C语言中的结构体
```
type
  Name = string # 此方式定义了一个类型别名，它和原始类型是一样，但是描述性更强
  Age = int
  Person = tuple[name: Name, age: Age] # Define data structures too.
  AnotherSyntax = tuple
    fieldOne: string
    secondField: int

var
  john: Person = (name: "John B.", age: 17)
  newage: int = 18 # It would be better to use Age than int

john.age = newage # But still works because int and Age are synonyms

type
  Cash = distinct int    # `distinct` makes a new type incompatible with its
  Desc = distinct string # base type.

var
  money: Cash = 100.Cash # `.Cash` converts the int to our type
  description: Desc  = "Interesting".Desc

when compileBadCode:
  john.age  = money        # Error! age is of type int and money is Cash
  john.name = description  # Compiler says: "No way!"
```

Enumerations：枚举类型
```
type
  Color = enum cRed, cBlue, cGreen
  Direction = enum # Alternative formatting
    dNorth
    dWest
    dEast
    dSouth
var
  orient = dNorth # `orient` is of type Direction, with the value `dNorth`
  pixel = cGreen # `pixel` is of type Color, with the value `cGreen`

discard dNorth > dEast # Enums are usually an "ordinal" type

# Subranges specify a limited valid range

type
  DieFaces = range[1..20] # Only an int from 1 to 20 is a valid value
var
  my_roll: DieFaces = 13

when compileBadCode:
  my_roll = 23 # Error!
```

Arrays：数组类型
```
type
  RollCounter = array[DieFaces, int]  # Arrays are fixed length and
  DirNames = array[Direction, string] # indexed by any ordinal type.
  Truths = array[42..44, bool]
var
  counter: RollCounter
  directions: DirNames
  possible: Truths

possible = [false, false, false] # Literal arrays are created with [V1,..,Vn]
possible[42] = true

directions[dNorth] = "Ahh. The Great White North!"
directions[dWest] = "No, don't go there."

my_roll = 13
counter[my_roll] += 1
counter[my_roll] += 1

var anotherArray = ["Default index", "starts at", "0"]
```

# 函数
Procedures：函数
```
type Answer = enum aYes, aNo

proc ask(question: string): Answer =
  echo(question, " (y/n)")
  while true:
    case readLine(stdin)
    of "y", "Y", "yes", "Yes":
      return Answer.aYes  # Enums can be qualified
    of "n", "N", "no", "No":
      return Answer.aNo
    else: echo("Please be clear: yes or no")

proc addSugar(amount: int = 2) = # Default amount is 2, returns nothing
  assert(amount > 0 and amount < 9000, "Crazy Sugar")
  for a in 1..amount:
    echo(a, " sugar...")

case ask("Would you like sugar in your tea?")
of aYes:
  addSugar(3)
of aNo:
  echo "Oh do take a little!"
  addSugar()
# No need for an `else` here. Only `yes` and `no` are possible.
```

## FFI
解释：全称Foreign Function Interface，译为外部函数接口，Nim中提供了现成的接口，只需遵循如下格式，即可调用C语言中的函数
```
proc strcmp(a, b: cstring): cint 
  {.importc: "strcmp", nodecl.}

let cmp = strcmp("C?", "Easy!")
```

# 函数用法
## encode
函数解释：nim中用于base64编解码的函数，除了可以编解码字符串，还可以编解码整数列表、字符列表
参考链接：https://nim-lang.org/docs/base64.html
```
import std/base64

let encoded = encode("Hello World")
assert encoded == "SGVsbG8gV29ybGQ="

let encodedInts = encode([1,2,3])
assert encodedInts == "AQID"
let encodedChars = encode(['h','e','y'])
assert encodedChars == "aGV5"

let decoded = decode("SGVsbG8gV29ybGQ=")
assert decoded == "Hello World"
```

## fmt
函数解释：nim中的fmt类似于python中的format，用法："abc {0}".format("out.nim")
```
"abc {}".fmt("out.nim")  # 输出：abc out.nim
```

## copyMem
函数原型：system.copyMem: proc (dest: pointer, source: pointer, size: Natural){.inline, noSideEffect, gcsafe, locks: 0.}
函数解释：从第二个参数的位置拷贝到第一个参数的位置，拷贝大小为第三个参数
说明1：addr是语法格式
参考链接：：vscode中的插件nim by Konstantin Zaitsev
```
copyMem(addr plaintext[0], addr ByteEvilContent[0], len(ByteEvilContent))
```

## writeFile
函数解释：将第二个参数表示的内容写入第一个参数表示的文件名
参考链接：vscode中的插件nim by Konstantin Zaitsev
```
writeFile(r"serv.nim", BinderTemplate)
```

# 参考链接
https://learnxinyminutes.com/docs/nim/
https://narimiran.github.io/nim-basics/
https://github.com/byt3bl33d3r/OffensiveNim
http://blog.nsfocus.net/nim-summary/