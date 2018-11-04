#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Hz 714

typedef struct dee{
    double re;
    double im;
} dft;

double shinpuku(dft xn)
{
    return sqrt((xn.re*xn.re) + (xn.im*xn.im));
}

double isou(dft xn)
{   
    if(xn.re ==  0) return 0;
    else if (xn.im == 0) return 0;
    return atan2(xn.im, xn.re);
}

double hanning(dft xn)
{
    return 0.5-(0.5 * cos((2*M_PI*xn.re)/Hz));
}

int main(int argc, char const *argv[])
{
    dft xn[Hz], Xn[Hz];
    int check = 0;
    int a, N;
    printf("dftなら1, idftなら0を入力\n");
    scanf("%d",&check);
    if(check == 1){
        int han = 0;
        printf("ハニングをかけるなら1を入力 = ");
        scanf("%d",&han);
        for(int i=0; i<Hz; i++){
            printf("xnを入力(%d回目) = ",i+1);
            scanf("%lf",&xn[i].re);
            if(han == 1) xn[i].re = hanning(xn[i]);
            xn[i].im = 0;
            Xn[i].re = 0;
            Xn[i].im = 0;
        }
        a = 1;
        N = 1;
        for(int i=0; i<Hz; i++){
            for(int j=0; j<Hz; j++){
                Xn[i].re += (xn[j].re * cos( ( (2*M_PI) /Hz) * j * i) + a* xn[j].im * sin( ( (2*M_PI) /Hz) * j * i));
                Xn[i].im += (xn[j].im * cos( ( (2*M_PI) /Hz) * j * i) - a* xn[j].re * sin( ( (2*M_PI) /Hz) * j * i));
            }
            Xn[i].re = Xn[i].re / N;
            Xn[i].im = Xn[i].im / N;
        }
    }else if(check == 0){
        for(int i=0; i<Hz; i++){
            printf("xnを入力(%d回目)\n実部と虚部はスペースで区切ってください = ",i+1);
            scanf("%lf %lf",&xn[i].re, &xn[i].im);
            Xn[i].re = 0;
            Xn[i].im = 0;
        }
        a = -1;
        N = Hz;
        for(int i=0; i<Hz; i++){
            for(int j=0; j<Hz; j++){
                Xn[i].re += (xn[j].re * cos( ( (2*M_PI) /Hz) * j * i) + a* xn[j].im * sin( ( (2*M_PI) /Hz) * j * i));
                Xn[i].im += (xn[j].im * cos( ( (2*M_PI) /Hz) * j * i) - a* xn[j].re * sin( ( (2*M_PI) /Hz) * j * i));
            }
            Xn[i].re = Xn[i].re / N;
            Xn[i].im = Xn[i].im / N;
        }
    }else if(check == 507){
        char name[256];
        FILE *fp;
        printf("filename = ");
        scanf("%s",&name);
        fp = fopen(name, "r");
        int han = 0;
        printf("ハニングをかけるなら1を入力 = ");
        scanf("%d",&han);
        for(int i=0; i<Hz; i++){
            fscanf(fp, "%lf", &xn[i].re);
            if(han == 1) xn[i].re = hanning(xn[i]);
            xn[i].im = 0;
            Xn[i].re = 0;
            Xn[i].im = 0;
        }
        a = 1;
        N = 1;
        for(int i=0; i<Hz; i++){
            for(int j=0; j<Hz; j++){
                Xn[i].re += (xn[j].re * cos( ( (2*M_PI) /Hz) * j * i) + a* xn[j].im * sin( ( (2*M_PI) /Hz) * j * i));
                Xn[i].im += (xn[j].im * cos( ( (2*M_PI) /Hz) * j * i) - a* xn[j].re * sin( ( (2*M_PI) /Hz) * j * i));
            }
            Xn[i].re = Xn[i].re / N;
            Xn[i].im = Xn[i].im / N;
        }
    }else{
        printf("終了します\n");
        return -1;
    }
    
    printf("結果\n");
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    if ((fp = fopen("位相.txt", "w")) == NULL) {
        printf("read_file open error.\n");
        exit(EXIT_FAILURE);
    }
    if ((fp2 = fopen("振幅.txt", "w")) == NULL) {
        printf("write_file open error.\n");
        exit(EXIT_FAILURE);
    }
    if ((fp3 = fopen("all.txt", "w")) == NULL) {
        printf("write_file open error.\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<Hz; i++){
        printf("Xn[%d]:%lf+%lfj\n",i ,Xn[i].re, Xn[i].im);
        fprintf(fp2, "%lf\n", shinpuku(Xn[i]));
        fprintf(fp, "%lf\n", isou(Xn[i]));
        fprintf(fp3, "%lf %lf\n", Xn[i].re, Xn[i].im);
    }

    return 0;
}
