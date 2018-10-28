#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 256

typedef struct {
    char id[4];
    unsigned int size;
    char form[4];
} riff_chunk;

typedef struct {
    char id[4];
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
    unsigned short data;
} data_chunk;

void change(char a[4], char b[4]) {
    for (int i=0; i<4; i++) {
        a[i] = b[i];
    }
}

int main() {
    riff_chunk riff;
    fmt_chunk fmt;
    data_chunk data;
    FILE *fp;
    FILE *fp2;
    int i, mode = 0, samples = 0;
    char filename[64], buf[BUF_SIZE];

    do {
        printf("1: wave -> text\n2: text -> wave\n");
        scanf("%d", &mode);
        printf("ファイル名を入力: ");
        scanf("%s", filename);

        if (mode == 1) {
            if ((fp = fopen(filename, "rb")) == NULL) {
                printf("read_file open error.\n");
                exit(EXIT_FAILURE);
            }
            if ((fp2 = fopen("output.txt", "w")) == NULL) {
                printf("write_file open error.\n");
                exit(EXIT_FAILURE);
            }
        } else if (mode == 2) {
            if ((fp = fopen(filename, "r")) == NULL) {
                printf("read_file open error.\n");
                exit(EXIT_FAILURE);
            }
            if ((fp2 = fopen("output.wav", "wb")) == NULL) {
                printf("write_file open error.\n");
                exit(EXIT_FAILURE);
            }
        } else printf("モードを選択してください");
    } while (mode != 1 && mode != 2);

    if (mode == 1) {
        /* -- head読み込み -- */
        fread(riff.id, sizeof(char), 4, fp);
        fread(&riff.size, sizeof(int), 1, fp);
        fread(riff.form, sizeof(char), 4, fp);
        fread(fmt.id, sizeof(char), 4, fp);
        fseek(fp, 4, SEEK_CUR);
        fread(&fmt.format_id, sizeof(short), 1, fp);
        fread(&fmt.channel, sizeof(short), 1, fp);
        fread(&fmt.fs, sizeof(int), 1, fp);
        fread(&fmt.data_sec, sizeof(int), 1, fp);
        fread(&fmt.block_size, sizeof(short), 1, fp);
        fread(&fmt.bit, sizeof(short), 1, fp);
        fmt.byte_samp = fmt.channel * (fmt.bit/8);
        fmt.byte_sec = fmt.fs * fmt.byte_samp;
        fread(data.id, sizeof(char), 4, fp);
        fread(&data.size, sizeof(int), 1, fp);
        int samples = data.size/2;
        double time = samples / (double)fmt.fs;

        /*
        printf("%s\n", riff.id);
        printf("filesize= %d\n", riff.size);
        printf("%s\n", riff.form);
        printf("channel= %d\n", fmt.channel);
        printf("fs= %d\n", fmt.fs);
        printf("data_sec= %d\n", fmt.data_sec);
        printf("block= %d\n", fmt.block_size);
        printf("bit= %d\n", fmt.bit);
        printf("%s\n", data.id);
        printf("data_size= %d\n", data.size);
        printf("samples= %d\n", samples);
        printf("time= %fs\n", time);
        */
        /* -- headの読み込み終了 -- */
        printf("--- 結果 ---\n");
        printf("ファイルサイズ　　　　 = %6d[byte]\n", riff.size);
        printf("チャネル数　　　　　　 = %6d\n", fmt.channel);
        printf("サンプリング周波数　　 = %6d[Hz]\n", fmt.fs);
        printf("量子化ビット　　　　　 = %6d\n", fmt.bit);
        printf("保存されているデータ数 = %6d\n", samples);
        printf("録音時間　　　　　　　 = %.4lf\n", time);

        /* -- ファイル書き込み txt -- */
        for (i=0; i<samples; i++) {
            fread(&data.data, sizeof(short), 1, fp);
            fprintf(fp2, "%d\n", data.data);
        }
    } else if (mode == 2) {
        while (fgets(buf, BUF_SIZE, fp) != NULL) {
            samples++;
        }
        printf("sample= %d\n", samples);
        fmt_chunk fmt2;
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
        fmt2.format_id = 1;
        fwrite(&fmt2.format_id, sizeof(short), 1, fp2);
        fmt2.channel = 1;
        fwrite(&fmt2.channel, sizeof(short), 1, fp2);
        fmt2.fs = 11025;
        fwrite(&fmt2.fs, sizeof(int), 1, fp2);
        fmt2.data_sec = 22050;
        fwrite(&fmt2.data_sec, sizeof(int), 1, fp2);
        fmt2.block_size = 2;
        fwrite(&fmt2.block_size, sizeof(short), 1, fp2);
        fmt2.bit = 16;
        fwrite(&fmt2.bit, sizeof(short), 1, fp2);
        change(save_str, "data");
        int datasize = samples * 2;
        fwrite(&datasize, sizeof(int), 1, fp2);
        fseek(fp, 0, SEEK_SET);
        for (i=0; i<datasize; i++) {
            fscanf(fp, "%d\n", &data);
            fwrite(&data, sizeof(short), 1, fp2);
        }
    }
    return 0;
}