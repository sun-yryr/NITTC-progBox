#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fsample (40 * 10 * 10 * 10)
#define CarFreg 1000
#define CarAmp 1

double cos_wave(int n, double a, double f, double p) {
    return a * cos((2 * M_PI * f * n)/fsample + p);
}

double BPSK_wave(int n, int m, int f, int a, int data[]) {
    return cos_wave(m, a, f, M_PI * data[n] - M_PI/2.0);
}

int main() {
    int data[6] = {1, 0, 1, 1, 0 ,1};
    int a = 1, f = 1000, p = 0;
    double ans;
    FILE *fp;
    if((fp = fopen("./sample_bpsk.txt", "w")) == NULL) {
        printf("file open error\n");
        return -1;
    }
    for(int i=0; i<6; i++) {
        for(int j=i*200; j<(i+1)*200; j++) {
            ans = BPSK_wave(i, j, f, a, data);
            fprintf(fp, "%.6lf %.6lf\n", (double)j/fsample, ans);
        }
    }
    return 0;
}