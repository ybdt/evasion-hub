```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 65534

/*
  参考链接：https://blog.csdn.net/qq_38130747/article/details/88602061
*/

int S[256];            //向量S
char T[256];           //向量T
int Key[256];          //随机生成的密钥
int KeyStream[MAX];    //密钥
char PlainText[MAX];   //明文
char CryptoText[MAX];  //密文
const char* WordList = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

//初始化S
void init_S() {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
}

//初始化密钥
void init_Key() {
    int index;
    srand(time(NULL));  // 根据当前时间，作为种子
    int keylen = int(double(rand()) / double(RAND_MAX) * 256);  // 随机获取一个密钥的长度
    for (int i = 0; i < keylen; i++) {
        index = int(double(rand()) / double(RAND_MAX) * 63);  // 生产密钥数组
        Key[i] = WordList[index];
    }
    for (int i = 0; i < 256; i++) {  // 初始化T[]
        T[i] = Key[i % keylen];
    }
}

//置换S
void  permute_S() {
    int temp;
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + T[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

//生成密钥流
void create_key_stream(char* text, int textLength) {
    int i, j;
    int temp, t;
    int index = 0;
    i = j = 0;
    while (textLength--) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        t = (S[i] + S[j]) % 256;
        KeyStream[index] = S[t];
        index++;
    }
}

//加密 && 解密
void Rc4EncryptText(char* text) {
    int textLength = strlen(text);
    init_S();
    init_Key();
    permute_S();
    create_key_stream(text, textLength);
    printf("\n============开始加密============\n");
    for (int i = 0; i < textLength; i++) {
        CryptoText[i] = char(KeyStream[i] ^ text[i]);  // 加密
    }
    for (int i = 0; i < textLength; i++) {
        printf("%c", CryptoText[i]);
    }
    printf("\n");
    printf("============开始解密============\n");
    for (int i = 0; i < textLength; i++) {
        PlainText[i] = char(KeyStream[i] ^ CryptoText[i]);  // 解密
    }
    for (int i = 0; i < textLength; i++) {
        printf("%c", PlainText[i]);
    }
    printf("\n");
    printf("============加解密完成============\n");
}

int main() {
    char text[] = "password";
    Rc4EncryptText(text);

    return 0;
}
```

上述代码只是完成字符串的加解密，对于二进制文件，还需额外处理，具体可参考：https://myzxcg.com/2022/01/字符串加密与Shellcode-隐藏/