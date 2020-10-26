var = "0000";

with open("dict.txt", "a") as f:
    while int(var) <= 9999:
        if 0 <= int(var) <= 8:  #此处如果是9的话，生成的10会变成100
            f.write(var + "\n");
            var = "000" + str(int(var) + 1);
        elif 9 <= int(var) <= 98:  #此处如果是99的话，生成的100会变成1000
            f.write(var + "\n");
            var = "00" + str(int(var) + 1);
        elif 99 <= int(var) <= 998:  #此处如果是999的话，生成的1000会变成10000
            f.write(var + "\n");
            var = "0" + str(int(var) + 1);
        else:
            f.write(var + "\n");
            var = str(int(var) + 1);
