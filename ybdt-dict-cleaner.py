#!/usr/bin/python3

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
