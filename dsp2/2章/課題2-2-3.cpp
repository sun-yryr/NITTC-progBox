#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

struct BITMAPFILEHEADER {
    /* data */
    ushort type;
    uint size;
    ushort reserved1;
    ushort reserved2;
    uint offBits;
};

struct BITMAPINFOHEADER {
    /* data */
    uint size;
    int width;
    int height;
    ushort planes;
    ushort bitCount;
    uint compression;
    uint sizeImage;
    int xPixPerMeter;
    int yPixPerMeter;
    uint clrUsed;
    uint clrImportant;
};

struct RGBDATA {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};


int main(int argc, char const *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("error\n");
        return 0;
    }
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    vector<vector<RGBDATA> > image;
    fread(&fileHeader.type, sizeof(short), 1, fp);
    return 0;
}