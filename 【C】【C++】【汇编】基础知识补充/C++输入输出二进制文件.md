# 从文件读取
```
char rawData[265728] = { 0 };
ifstream i_file;
i_file.open("beacon-x64.bin", ios::binary | ios::in | ios::out);
i_file.read(rawData, sizeof(rawData));
```

# 输出到文件
```
// 注意，程序不会自己创建文件a.bin，需要先创建a.bin
#include <fstream>

using namespace std;

int main() {
    char write_buf[100] = { 1 };
    ofstream o_file;
    o_file.open("a.bin", ios::binary | ios::in | ios::out);
    o_file.write(write_buf, sizeof(write_buf));

    return 0;
}
```

# 参考链接
C++编程实战宝典 郝军 等编著 -》第15章 流操作（拿出点时间学习一下）