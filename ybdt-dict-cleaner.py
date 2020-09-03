#!/usr/bin/env python3

import sys

def cut_repeat(dict):
    f = open("ybdt-dict-content.txt", "a");#if not exist, create it, if exist, do nothing
    f.close();

    f_new = open(dict, "r");
    f_old = open("ybdt-dict-content.txt", "r");
    tmp = f_old.readlines();
    print( "The old file count is: " + str(len(tmp)) );
    #print("The old file is:");
    #print(tmp);
    tmp_ = [];#create an empty array to store element without \n
    for line in tmp:
        tmp_.append( line.strip("\n") );
    lines = f_new.readlines();
    print("The new file count is: " + str(len(lines)) );
    #print("The new file is:");
    #print(lines);
    count = 0;#counter for repeated element
    print("The repeated element is: ");
    for line in lines:
        if line.strip("\n") not in tmp_:
            tmp_.append( line.strip("\n") );
        else:
            print( line.strip("\n") );
            count = count + 1;
    print( "The repeated count is: " + str(count) );
    print( "The final count is: " + str(len(tmp_)) );
    f_new.close();
    f_old.close();
    
    f = open("ybdt-dict-content.txt", "w");
    for line in tmp_:
        f.write(line + "\n");
    f.close();

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 ybdt-dict-cleaner.py path_to_dict");
        print("Example: python3 ybdt-dict-cleaner.py dict.txt");
        exit();
    else:
        dict = sys.argv[1];
    
    cut_repeat(dict);

if __name__ == "__main__":
    main();