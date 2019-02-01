#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fsample (40 * 10 * 10 * 10)
#define CarFreg 1000
#define CarAmp 1
#define BitN 6
#define BitRate 200
#define LPFactor 0.95

double cos_wave(int n, double a, double f, double p) {
    return a * cos((2 * M_PI * f * n)/fsample + p);
}

double ASK_wave(int n, int m, int f, int a, double data[]) {
    return data[n] * cos_wave(m, a, f, - M_PI/2.0);
}

int main() {
    int data[BitN] = {1, 0, 1, 1, 0 ,1};
    double in[BitN*BitRate];
    double out[BitN*BitRate];
    int a = 1, f = 1000, p = 0;
    double ans, tmp;
    FILE *fp;
    if((fp = fopen("./sample_ask.txt", "r")) == NULL) {
        printf("file open error\n");
        return -1;
    }
    for(int i=0; i<BitN; i++) {
        for(int j=i*BitRate; j<(i+1)*BitRate; j++) {
            fscanf(fp, "%lf %lf\n", &tmp, &in[j]);
            in[j] = ASK_wave(j, j, f, a, in);
        }
    }
    fclose(fp);


    if((fp = fopen("./sample_askout.txt", "w")) == NULL) {
        printf("file open error\n");
        return -1;
    }
    out[0] = in[0];
    for(int i=1; i<BitN*BitRate; i++) {
        out[i] = in[i] + (out[i-1] - in[i]) * LPFactor;
        fprintf(fp, "%.6lf %.6lf\n", (double)i/fsample, out[i]);
    }
    return 0;
}