#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define LOG printf("line = %d\n", __LINE__);

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
void twid(Complex[], int);
Complex conjugate(Complex);
double absolute(Complex);
double absolute2(Complex);
Polar polarTrans(Complex);
Complex complexTrans(Polar);
void fft(Complex[], int);
void bitReversal(int[], int);
void dft(Complex[], int);

int main() {
    char filename[256];
    FILE *fp;
    int size, i=0;
    printf("Hello World!\n");
    printf("filename >> ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("read_file open error.\n");
        exit(EXIT_FAILURE);
    }
    printf("何点FFT: ");
    scanf("%d", &size);
    Complex *data;
    data = (Complex*)malloc(size * sizeof(Complex));
    for(i=0; i<size; i++) {
        data[i].re = 0;
        data[i].im = 0;
        fscanf(fp, "%lf %lf\n", &data[i].re, &data[i].im);
    }
    //fft(data, size);
    dft(data, size);
    for(i=0; i<size; i++) {
        printf("[%d]: %f + %lf j\n", i, data[i].re, data[i].im);
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

void twid(Complex A[], int N) {
    for(int i=0; i<N/2; i++) {
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

void fft(Complex old[], int N) {
    int i, j;
    int *check, *bit;
    Complex *twin, *new;
    check = (int*)malloc(N * sizeof(int));
    bit = (int*)malloc(N * sizeof(int));
    twin = (Complex*)malloc(N/2 * sizeof(Complex));
    new = (Complex*)malloc(N * sizeof(Complex));
    bitReversal(bit, N);
    twid(twin, N);
    for(i=0; i<N; i++) {
        new[bit[i]] = old[i];
        check[i] = 0;
    }
    for(i=0; i<N; i++) {
        old[i] = new[i];
        //printf("%lf %lf   %d\n", old[i].re, old[i].im, bit[i]);
    }
    int p = N / 2;
    //段数繰り返し
    for(i=0; i<(int)log2(N); i++, p/=2) {
        int nk = 0;
        for(j=0; j<N; j++) {
            int next = j + (int)pow(2, i);
            if(check[j] == 0) {
                check[j] = 1; check[next] = 1;
                Complex tmp = multiplication(old[next], twin[nk]);
                //printf("(%lf %lf) * (%lf %lf) = (%lf %lf)\n", old[next].re, old[next].im, twin[nk].re, twin[nk].im, tmp.re, tmp.im);
                Complex ad = addition(old[j], tmp);
                //printf("(%lf %lf) + (%lf %lf) = (%lf %lf)\n", old[j].re, old[j].im, tmp.re, tmp.im, ad.re, ad.im);
                old[next] = subtraction(old[j], tmp);
                //printf("(%lf %lf) - (%lf %lf) = (%lf %lf)\n", old[j].re, old[j].im, tmp.re, tmp.im, old[next].re, old[next].im);
                old[j] = ad;
                if((i!=0) && (nk+p) < (N/2)) nk += p;
                else {
                    nk = 0;
                }
                //printf("\n");
            }
        }
        for(int as=0; as<N; as++) check[as] = 0;
    }
}

void bitReversal(int bit[], int N) {
    int i, j;
    int r = (int)log2(N);
    for(i=0; i<N; i++) {
        bit[i] = 0;
        for(j=0; j<r; j++) {
            bit[i] += ((i >> j)& 1) << (r - j - 1);
        }
    }
}

void dft(Complex Xn[], int N) {
    Complex *xn;
    xn = (Complex*)malloc(N * sizeof(Complex));
    int i;
    for(i=0; i<N; i++) {
        xn[i].re = Xn[i].re;
        xn[i].im = Xn[i].im;
        Xn[i].re = 0;
        Xn[i].im = 0;
    }
    for(i=0; i<N; i++){
        for(int j=0; j<N; j++){
            Xn[i].re += (xn[j].re * cos( ( (2*M_PI) /N) * j * i) + xn[j].im * sin( ( (2*M_PI) /N) * j * i));
            Xn[i].im += (xn[j].im * cos( ( (2*M_PI) /N) * j * i) - xn[j].re * sin( ( (2*M_PI) /N) * j * i));
        }
    }
}