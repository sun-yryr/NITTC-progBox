#include <stdio.h>
#include <math.h>

typedef struct dee {
    double re;
    double im;
} Complex;

//プロトタイプ宣言
Complex addition(Complex, Complex);
Complex subtraction(Complex, Complex);
Complex multiplication(Complex, Complex);
Complex division(Complex, Complex);

int main() {
    printf("Hello World!\n");
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
    return returnData;
}

Complex division(Complex A, Complex B) {
    Complex returnData;
    return returnData;
}