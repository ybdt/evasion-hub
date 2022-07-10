def main():
    with open("a.txt", "w", encoding="UTF-8") as fw:
        for i in range(100000):
            if len(str(i)) == 1:
                final_i = "0000" + str(i)
            elif len(str(i)) == 2:
                final_i = "000" + str(i)
            elif len(str(i)) == 3:
                final_i = "00" + str(i)
            elif len(str(i)) == 4:
                final_i = "0" + str(i)
            elif len(str(i)) == 5:
                final_i = str(i)
            
            fw.write(final_i + "\n")

main()