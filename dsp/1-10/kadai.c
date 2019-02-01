#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50

double gauss() {
    static double dispersion = 1, average = 0;
    double x1, x2, gauss;
    x1 = (double)rand()/(RAND_MAX);
    x2 = (double)rand()/(RAND_MAX);
    gauss = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2) * sqrt(dispersion) + average;
    return gauss;
}

double colored() {
    double color;
    static double old_color = 0;
    color = gauss() + 0.99 * old_color;
    old_color = color;
    return color;
}

void lms_algo(double fillter[], double x[], double e[]) {
}

int main() {
    double wn[N], hn[N], d, y ,e;
    FILE *fp;
    if((fp = fopen("./wn.txt", "r")) == NULL) {
        printf("load error\n");
    }   
    for(int i=0; i<N; i++) 
        fscanf(fp, "%lf\n", wn[i]);
    
    return 0;
}