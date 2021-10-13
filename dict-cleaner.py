#!/usr/bin/python3

'''
功能：可对指定文件（如dict.txt）去重，或将新字典添加到旧字典尾部后对旧字典去重，生成去重后的新文件（新文件名dict-new.txt）

2020/12/30-发现有些字典的换行符是"\n"，有些字典的换行符是"\r\n"
新增功能：对linux和windows下换行符做适配

2020/12/30-发现有些字典的每行首尾包含空格或制表符
新增功能：去重的同时会去除每行首尾的空格符(" ")、回车符("\r")、换行符("\n")、制表符("\t")

2020/12/31-发现有些字典的默认字符集不是UTF-8
新增功能：先识别目标字典的字符集，再用指定字符集打开字典
'''

import sys
import platform
import chardet

if platform.system() == "Linux":
    return_line = "\n";
elif platform.system() == "Windows":
    return_line = "\r\n";

#识别待读取文件的字符集
def charset_detect(dict):
    with open(dict, "rb") as f:
        charset_encoding = chardet.detect( f.read() )["encoding"];
        print("文件字符编码：" + charset_encoding);
        return charset_encoding;

def cut_repeat(dict):
    charset_encoding = charset_detect(dict);
    
    with open(dict, "r", encoding=charset_encoding) as f_original:
        dict_name = dict.split(".")[0]
        with open(dict_name + "-new" + ".txt", "a") as f_new:
            lines = f_original.readlines();
            print( "The original file count is: " + str( len(lines) ) );
            
            #创建一个临时数组，存储每行中去掉换行符后的字符部分
            tmp = [];

            #每次添加到数组前，比对是否在数组中出现过，没出现过则添加到数组中
            for line in lines:
                if line.strip() not in tmp:
                    tmp.append( line.strip() );
                else:
                    continue;
            
            print( "The new file count is: " + str( len(tmp) ) );

            #将去重后的临时数组写入新的文件
            for item in tmp:
                f_new.write(item + return_line);

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 ybdt-dict-cleaner.py path_to_dict");
        print("Example: python3 ybdt-dict-cleaner.py dict.txt");
        exit();
    else:
        dict = sys.argv[1];
    
    cut_repeat(dict);

main();
