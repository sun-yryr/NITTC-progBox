#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double re;
    double im;
} Complex;

typedef struct {
    double value;
    double theta;
} Polar;

//プロトタイプ宣言
Complex addition(Complex, Complex);
Complex subtraction(Complex, Complex);
Complex multiplication(Complex, Complex);
Complex division(Complex, Complex);
void twid(Complex*, int);
Complex conjugate(Complex);
double absolute(Complex);
double absolute2(Complex);
Polar polarTrans(Complex);
Complex complexTrans(Polar);
void fft(Complex*, Complex*, int);
void bitReversal(int*, int);

int main() {
    printf("Hello World!\n");
    int bit[8] = {0};
    bitReversal(bit, (sizeof(bit)/sizeof(bit[0])));
    for(int i=0; i<8; i++) {
        printf("%d\n", bit[i]);
    }
    return 0;
}

Complex addition(Complex A, Complex B) {
    Complex returnData;
    returnData.re = A.re + B.re;
    returnData.im = A.im + B.im;
    return returnData;
}

Complex subtraction(Complex A, Complex B) {
    Complex returnData;
    returnData.re = A.re - B.re;
    returnData.im = A.im - B.im;
    return returnData;
}

Complex multiplication(Complex A, Complex B) {
    Complex returnData;
    double a = A.re,
        b = A.im,
        c = B.re,
        d = B.im;
    returnData.re = (a * c) - (b * d);
    returnData.im = (b * c) + (a * d);
    return returnData;
}

Complex division(Complex A, Complex B) {
    Complex returnData;
    double a = A.re,
        b = A.im,
        c = B.re,
        d = B.im;
    double nnn = (c * c) + (d * d);
    returnData.re = ((a * c) + (b * d)) / nnn;
    returnData.im = ((b * c) - (a * d)) / nnn;
    return returnData;
}

void twid(Complex *A, int N) {
    for(int i=0; i<N; i++) {
        double theta = (2 * M_PI) - ((2 * M_PI) / N) * i;
        A[i].re = cos(theta);
        A[i].im = sin(theta);
    }
}

Complex conjugate(Complex A) {
    Complex returnData;
    returnData.re = A.re;
    returnData.im = -1 * A.im;
    return returnData;
}

double absolute(Complex A) {
    //return sqrt((A.re * A.re) + (A.im * A.im));
    return sqrt(absolute2(A));
}

double absolute2(Complex A) {
    Complex returnData = multiplication(A, conjugate(A));
    return returnData.re;
}

Polar polarTrans(Complex A) {
    Polar returnData;
    returnData.value = absolute(A);
    returnData.theta = atan(A.im / A.re);
    return returnData;
}

Complex complexTrans(Polar A) {
    Complex returnData;
    returnData.re = A.value * cos(A.theta);
    returnData.im = A.value * sin(A.theta);
    return returnData;
}

void fft(Complex *old, Complex *twin, int N) {
    
}

void bitReversal(int *bit, int N) {
    int i, j;
    int m = (int)log2(N);
    for(i=0; i<N; i++) {
        bit[i] = 0;
        for(j=0; j<m; j++) {
            bit[i] += ((i >> j)& 1) << (m - j - 1);
        }
    }
}