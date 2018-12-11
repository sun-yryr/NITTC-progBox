//H30 dsp 1-8 4J38
#include <stdio.h>
#include <stdlib.h>


void fillter(int[], double[], int[], int);

int main() {
    char filename[256];
    FILE *fp1, *fp2, *fp3;
    int size;
    int *input_x, *output;
    double *input_h;
    printf("H30 dsp 1-8 4J38\n");

    //ファイル読み込み
    printf("入力ファイル名:");
    scanf("%s", filename);
    if ((fp1 = fopen(filename, "r")) == NULL) {
        printf("read_file open error.\n");
        exit(EXIT_FAILURE);
    }
    printf("フィルタファイル名:");
    scanf("%s", filename);
    if ((fp2 = fopen(filename, "r")) == NULL) {
        printf("read_file open error.\n");
        exit(EXIT_FAILURE);
    }
    printf("サンプル数:");
    scanf("%d", &size);
    if ((fp3 = fopen("./data/output.txt", "w")) == NULL) {
        printf("write_file open error.\n");
        exit(EXIT_FAILURE);
    }

    //データ読み込み
    input_x = (int*)malloc(size * sizeof(int));
    input_h = (double*)malloc(size * sizeof(double));
    output = (int*)malloc(size * sizeof(int));
    for(int i=0; i<size; i++) {
        fscanf(fp1, "%d\n", &input_x[i]); //ifft
        fscanf(fp2, "%lf\n", &input_h[i]);
    }

    fillter(input_x, input_h, output, size);

    //ファイル書き込み
    for(int i=0; i<size; i++) {
        fprintf(fp3, "%d\n", output[i]);
    }

    return 0;
}

void fillter(int input_x[], double input_h[], int output[], int N) {
    int i, j;
    int *new_x;
    new_x = (int*)malloc(N * sizeof(int));
    for(i=0; i<N; i++) {
        for(j=N-1; j!=0; j--) new_x[j] = new_x[j-1];
        new_x[0] = input_x[i];
        double answer = 0;
        for(j=0; j<N; j++) answer += new_x[j] * input_h[j];
        output[i] = answer;
        //if(i%20==0) printf("aaa\n");
    }
}