# -*- cording: utf-8 -*-


import numpy as np
from pathlib import Path

# PATH
READPATH = "./ke2/data/"
WRITEPATH = "./ke2/average/"

def main():
    """
    p = Path(READPATH)
    for n in list(p.glob("*.txt")):
        print(n)
    """
    for i in range(1, 47):
        if (i < 10):
            number = "0" + str(i)
        else:
            number = str(i)
        f = open(READPATH + "c" + number + ".txt")
        # readlinesでfor回す
        arr_ave = np.zeros(196, dtype=float)
        for i in range(180):
            dl_data = np.zeros(196, dtype=float)
            for j in range(196):
                line = f.readline()
                dl_data[j] = float(line)
            arr_ave = arr_ave + dl_data
        arr_ave = arr_ave / 196.0
        tmp_ = map(str, arr_ave)
        str_ = '\n'.join(tmp_)
        f_w = open(WRITEPATH + "mean" + number + ".txt", mode="w")
        f_w.write(str_)
        f.close()
        f_w.close()
    

if __name__ == "__main__":
    main()