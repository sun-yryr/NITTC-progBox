#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define fsample (40 * 10 * 10 * 10)

double sin_wave(int n, double a, double f, double p) {
    return a * sin((2 * M_PI * f * n)/fsample + p);
}

int main() {
    int a = 1, f = 200, p = 0;
    double ans;
    FILE *fp;
    if((fp = fopen("./sample_sin.txt", "w")) == NULL) {
        printf("file open error\n");
        return -1;
    }
    for(int i=0; i<1000; i++) {
        ans = sin_wave(i, a, f, p);
        fprintf(fp, "%.6lf %.6lf\n", (double)i/fsample, ans);
    }
    return 0;
}