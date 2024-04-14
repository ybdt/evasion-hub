```
#define _CRT_SECURE_NO_WARNINGS  // 允许使用不安全的函数

#include <stdio.h>
#include <stdlib.h>

//获取文件大小
int getFileSize(char* path) {
	FILE* fp = fopen(path, "rt");
	if (fp == NULL) {
		printf("文件打开失败！");
		return -1;
	}
	else {
		fseek(fp, 0, SEEK_END);
		int length = ftell(fp);
		printf("文件大小为：%d\n", length);
		return length;
	}
}

//对文件进行加密
void encrypt(char* oldPath, char* newPath) {
	FILE *fr, *fw;
	fr = fopen(oldPath, "rb");
	fw = fopen(newPath, "wb");
	if (fr == NULL || fw == NULL) {
		printf("打开或创建文件失败！");
	}
	else {
		int length = getFileSize(oldPath);
		char* p = (char*)malloc(length * sizeof(char));
		fread(p, sizeof(char), length, fr);
		for (int i = 0; i < length; i++) {
			p[i] ^= 'QWE';
		}
		fwrite(p, sizeof(char), length, fw);
		fclose(fr);
		fclose(fw);
	}
}

//对文件进行解密
void decrypt(char* oldPath, char* newPath) {
	FILE *fr, *fw;
	fr = fopen(oldPath, "rb");
	fw = fopen(newPath, "wb");
	if (fr == NULL || fw == NULL) {
		printf("打开或创建文件失败！");
	}
	else {
		int length = getFileSize(oldPath);
		char* p = (char*)malloc(length * sizeof(char));
		fread(p, sizeof(char), length, fr);
		for (int i = 0; i < length; i++) {
			p[i] ^= 'QWE';
		}
		fwrite(p, sizeof(char), length, fw);
		fclose(fr);
		fclose(fw);
	}
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: Encryptor.exe putty-x64.exe putty-x64-encrypt.exe putty-x64-decrypt.exe\n");
	}
	else {
		char* original_path = argv[1];
		char* encrypt_path = argv[2];
		char* decrypt_path = argv[3];

		encrypt(original_path, encrypt_path);
		decrypt(encrypt_path, decrypt_path);
	}
	
	return 0;

}
```

代码如上，可基于putty-x64.exe进行测试，经测试，putty-x64-decrypt.exe可成功运行