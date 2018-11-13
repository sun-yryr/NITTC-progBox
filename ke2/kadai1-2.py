# -*- cording: utf-8 -*-


import numpy as np
from pathlib import Path

# PATH
READPATH = "./ke2/data/"
WRITEPATH = "./ke2/dispersion/"

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
        dl_data = np.zeros((180, 196))
        for i in range(180):
            for j in range(196):
                line = f.readline()
                dl_data[i][j] = float(line)
        arr_disp = np.cov(dl_data, rowvar=False)
        f_w = open(WRITEPATH + "sigma" + number + ".txt", mode="w")
        for d in arr_disp:
            tmp_ = map(str, d)
            str_ = '\n'.join(tmp_)
            f_w.write(str_ + "\n")
        f.close()
        f_w.close()
    

if __name__ == "__main__":
    main()