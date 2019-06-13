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
    char type[2] = {'B','M'};
    uint size = 43254;
    ushort reserved1 = 0;
    ushort reserved2 = 0;
    uint offBits = 54;
};

struct BITMAPINFOHEADER {
    /* data */
    uint size = 40;
    int width = 120;
    int height = 120;
    ushort planes = 1;
    ushort bitCount = 24;
    uint compression = 0;
    uint sizeImage = 43200;
    int xPixPerMeter = 0;
    int yPixPerMeter = 0;
    uint clrUsed = 0;
    uint clrImportant = 0;
};

struct RGBDATA {
    uint R;
    uint G;
    uint B;
    uint Reserved;
};

struct BITMAP {
    BITMAPFILEHEADER file;
    BITMAPINFOHEADER info;
    vector<vector<RGBDATA> > image;
};

// 宣言
void load_bitmap_file(FILE *fp, BITMAP& bmpfile);
void write_bitmap_file(FILE *fp, BITMAP bmpfile);
void display_RGB(RGBDATA a);
void display_infomation(BITMAP bmpfile);

int main(int argc, char const *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "wb");
    if (fp == NULL) {
        printf("error\n");
        return 0;
    }
    BITMAP bmpfile;
    RGBDATA tmp = {0,0,0,0};
    bmpfile.image = vector<vector<RGBDATA> >(bmpfile.info.height, vector<RGBDATA>(bmpfile.info.width, tmp));
    write_bitmap_file(fp, bmpfile);
    return 0;
}

void write_bitmap_file(FILE *fp, BITMAP bmpfile) {
    // file header 書き込み
    fseek(fp, 0, SEEK_SET);
    fwrite(bmpfile.file.type, 1, 2, fp);
    fwrite(&bmpfile.file.size, 4, 1, fp);
    fwrite(&bmpfile.file.reserved1, 2, 1, fp);
    fwrite(&bmpfile.file.reserved2, 2, 1, fp);
    fwrite(&bmpfile.file.offBits, 4, 1, fp);
    // info header 書き込み
    fwrite(&bmpfile.info.size, 4, 1, fp);
    fwrite(&bmpfile.info.width, 4, 1, fp);
    fwrite(&bmpfile.info.height, 4, 1, fp);
    fwrite(&bmpfile.info.planes, 2, 1, fp);
    fwrite(&bmpfile.info.bitCount, 2, 1, fp);
    fwrite(&bmpfile.info.compression, 4, 1, fp);
    fwrite(&bmpfile.info.sizeImage, 4, 1, fp);
    fwrite(&bmpfile.info.xPixPerMeter, 4, 1, fp);
    fwrite(&bmpfile.info.yPixPerMeter, 4, 1, fp);
    fwrite(&bmpfile.info.clrUsed, 4, 1, fp);
    fwrite(&bmpfile.info.clrImportant, 4, 1, fp);
    // RGBDATA 書き込み
    int height = abs(bmpfile.info.height);
    int width = abs(bmpfile.info.width);
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            //BGR
            fwrite(&bmpfile.image[i][j].B, 1, 1, fp);
            fwrite(&bmpfile.image[i][j].G, 1 ,1, fp);
            fwrite(&bmpfile.image[i][j].R, 1, 1, fp);
            if (bmpfile.info.bitCount == 32) fwrite(&bmpfile.image[i][j].Reserved, 1, 1, fp);
        }
    }
}

void display_RGB(RGBDATA a) {
    printf("%3d, %3d, %3d\n", a.R, a.G, a.B);
}

void display_infomation(BITMAP bmpfile) {
    printf("-----BitMap FILE-----\n");
    printf("bfType : %s\n", bmpfile.file.type);
    printf("bfSize : %d\n", bmpfile.file.size);
    printf("bfReserved1 : %d\n", bmpfile.file.reserved1);
    printf("bfReserved2 : %d\n", bmpfile.file.reserved2);
    printf("bfOffBits : %d\n", bmpfile.file.offBits);
    
    printf("\n-----BitMap Info-----\n");
    printf("biSize : %d\n", bmpfile.info.size);
    printf("biWidth : %d\n", bmpfile.info.width);
    printf("biHeight : %d\n", bmpfile.info.height);
    printf("biPlanes : %d\n", bmpfile.info.planes);
    printf("biBitCount : %d\n", bmpfile.info.bitCount);
    printf("biCompression : %d\n", bmpfile.info.compression);
    printf("biSizeImage : %d\n", bmpfile.info.sizeImage);
    printf("biXPixPerMeter : %d\n", bmpfile.info.xPixPerMeter);
    printf("biYPixPerMeter : %d\n", bmpfile.info.yPixPerMeter);
    printf("biClrUesd : %d\n", bmpfile.info.clrUsed);
    printf("biClrImportant : %d\n", bmpfile.info.clrImportant);
}