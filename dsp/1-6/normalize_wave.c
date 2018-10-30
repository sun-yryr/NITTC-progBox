//normalize_wave.c
/* H30 DSP1-6 4J38 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

typedef struct {
    char id[4];
    unsigned int size;
    char form[4];
} riff_chunk;

typedef struct {
    char id[4];
    unsigned int size;
    unsigned short format_id;
    unsigned short channel;
    unsigned int fs;
    unsigned int byte_sec;
    unsigned short byte_samp;
    unsigned short bit;
    unsigned int data_sec;
    unsigned short block_size;
} fmt_chunk;

typedef struct {
    char id[4];
    unsigned int size;
    unsigned int data;
} fact_chunk;

typedef struct {
    char id[4];
    unsigned int size;
    short data;
} data_chunk;

void change(char a[4], char b[4]) {
    for (int i=0; i<4; i++) {
        a[i] = b[i];
    }
}

int main() {
    riff_chunk riff;
    fmt_chunk fmt;
    fact_chunk fact;
    data_chunk data;
    FILE *fp;
    FILE *fp2;
    int i, samples = 0;
    char filename[64], buf[BUF_SIZE];

    printf("ファイル名.wavを入力: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("read_file open error.\n");
        exit(EXIT_FAILURE);
    }
    if ((fp2 = fopen("./data/music.wav", "wb")) == NULL) {
        printf("write_file open error.\n");
        exit(EXIT_FAILURE);
    }

    // riff
    fread(riff.id, sizeof(char), 4, fp);
    fread(&riff.size, sizeof(int), 1, fp);
    fread(riff.form, sizeof(char), 4, fp);
    // fmt
    fread(fmt.id, sizeof(char), 4, fp);
    fread(&fmt.size, sizeof(int), 1, fp);
    fread(&fmt.format_id, sizeof(short), 1, fp);
    fmt.size -= sizeof(short);
    fread(&fmt.channel, sizeof(short), 1, fp);
    fmt.size -= sizeof(short);
    fread(&fmt.fs, sizeof(int), 1, fp);
    fmt.size -= sizeof(int);
    fread(&fmt.data_sec, sizeof(int), 1, fp);
    fmt.size -= sizeof(int);
    fread(&fmt.block_size, sizeof(short), 1, fp);
    fmt.size -= sizeof(short);
    fread(&fmt.bit, sizeof(short), 1, fp);
    fmt.size -= sizeof(short);
    fmt.byte_samp = fmt.channel * (fmt.bit/8);
    fmt.byte_sec = fmt.fs * fmt.byte_samp;
    fseek(fp, fmt.size, SEEK_CUR);
    // fact
    fread(fact.id, sizeof(char), 4, fp);
    fread(&fact.size, sizeof(int), 1, fp);
    fseek(fp, fact.size, SEEK_CUR);
    // data
    fread(data.id, sizeof(char), 4, fp);
    fread(&data.size, sizeof(int), 1, fp);
    samples = data.size/2;
    double time = samples / (double)fmt.fs;

    /* -- headの読み込み終了 -- */
    printf("--- 結果 ---\n");
    printf("ファイルサイズ　　　　 = %6d[byte]\n", riff.size);
    printf("チャネル数　　　　　　 = %6d\n", fmt.channel);
    printf("サンプリング周波数　　 = %6d[Hz]\n", fmt.fs);
    printf("量子化ビット　　　　　 = %6d\n", fmt.bit);
    printf("保存されているデータ数 = %6d\n", samples);
    printf("録音時間　　　　　　　 = %.4lf\n", time);

    /* -- waveへ書き込み -- */
    char save_str[4] = "RIFF";
    fwrite(save_str, sizeof(char), 4, fp2);
    //サンプル数*2 + 44 - 8
    int filesize = (samples * 2) + 36;
    fwrite(&filesize, sizeof(int), 1, fp2);
    change(save_str, "WAVE");
    fwrite(save_str, sizeof(char), 4, fp2);
    change(save_str, "fmt ");
    fwrite(save_str, sizeof(char), 4, fp2);
    int fmtsize = 16;
    fwrite(&fmtsize, sizeof(int), 1, fp2);
    fwrite(&fmt.format_id, sizeof(short), 1, fp2);
    fwrite(&fmt.channel, sizeof(short), 1, fp2);
    fwrite(&fmt.fs, sizeof(int), 1, fp2);
    fwrite(&fmt.data_sec, sizeof(int), 1, fp2);
    fwrite(&fmt.block_size, sizeof(short), 1, fp2);
    fwrite(&fmt.bit, sizeof(short), 1, fp2);
    change(save_str, "data");
    fwrite(save_str, sizeof(char), 4, fp2);
    int datasize = samples * 2;
    fwrite(&datasize, sizeof(int), 1, fp2);
    for (i=0; i<datasize; i++) {
        fread(&data.data, sizeof(short), 1, fp);
        fwrite(&data.data, sizeof(short), 1, fp2);
    }
}