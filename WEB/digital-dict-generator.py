#!/usr/bin/python3

def main():
    with open("dict.txt", "w") as f:
        for i in range(0, 1000000):
            len_for_i = len( str(i) );
            if len_for_i != 6:
                new_i = "0" * (6-len_for_i) + str(i);
                f.write(new_i + "\n");
            else:
                f.write(str(i) + "\n");

main();
