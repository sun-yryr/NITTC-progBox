#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *A, *B, *C, *R;
double qri = 1e-8; //収束条件
//int sample;
#define sample 196

int* getAbsolute(double[]);
double getabs(double[]);
void createIdentity(int);
double elim(double[], int, int);
void makeR(int, int, double);


int main() {
    char filename[256];
    int i, j;
    FILE *fp;
    A = (double*)malloc(sample * sample * sizeof(double));
    B = (double*)malloc(sample * sample * sizeof(double));
    C = (double*)malloc(sample * sample * sizeof(double));


    for (int out=1; out<=47; out++) {
        snprintf(filename, 256, "./dispersion/sigma%02d.txt", out);
        printf("read[%s]\n", filename);
        if ((fp = fopen(filename, "r")) == NULL) {
            printf("read_file open error.\n");
            exit(EXIT_FAILURE);
        }

        for (i=0; i<sample; i++) {
            for (j=0; j<sample; j++) {
                fscanf(fp, "%lf¥n", &A[(sample * i) + j]);
                B[(sample * i) + j] = A[(sample * i) + j];
            }
        }
        fclose(fp);
        /* ---------------------------------------------------- */
        int step = 0;
        int *index;
        int p, q;
        double phi;

        createIdentity(sample);
        double non_diag_max = getabs(B);
        while(non_diag_max >= qri) {
            step++;
            index = getAbsolute(B);
            p = index[0];
            q = index[1];
            //printf("%d, %d     %lf\n", p, q, B[(sample * p) + q]);
            phi = elim(B, p, q);
            makeR(p, q, phi);
            non_diag_max = getabs(B);
            printf("step=%d   dig_max=%lf\n", step, non_diag_max);
        }
        /* ----------------------------------------------------- */

        snprintf(filename, 256, "./jacobi/data%02d.txt", out);
        if ((fp = fopen(filename, "w")) == NULL) {
            printf("write_file open error.\n");
            exit(EXIT_FAILURE);
        }
        for (i=0; i<sample; i++) {
            for (j=0; j<sample; j++) {
                fprintf(fp, "%lf\n", R[(sample * i) + j]);
            }
        }
        fclose(fp);
    }

    return 0;
}

double getabs(double data[]) {
    double max = 0;
    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            if (i == j) C[(sample * i) + j] = 0;
            else C[(sample * i) + j] = fabs(data[(sample * i) + j]);

            if (C[(sample * i) + j] > max) max = C[(sample * i) + j];
        }
    }
    return max;
}


/* 
    非対角成分の絶対値の最大値の添字を返却する
    返り値は[i, j]
*/
int* getAbsolute(double data[]) {
    int i,j;
    double max = 0;
    int o_i, o_j;
    for (i=0; i<sample; i++) {
        for (j=0; j<sample; j++) {
            if (i == j) C[(sample * i) + j] = 0;
            else C[(sample * i) + j] = fabs(data[(sample * i) + j]);
            
            if (C[(sample * i) + j] > max) {
                max = C[(sample * i) + j];
                o_i = i;    o_j = j;
            }
        }
    }
    int rd[2] = {o_i, o_j};
    return rd;
}

void createIdentity(int N) {
    R = (double*)malloc(N * N * sizeof(double));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) R[ (N*i) + j ] = 1;
            else R[ (N*i) + j ] = 0;
        }
    }
}

double elim(double data[], int p, int q) {
    double *D;
    double phi;
    D = (double*)malloc(sample * sample * sizeof(double));
    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            D[(sample * i) + j] = data[(sample * i) + j];
        }
    }

    if ((data[(sample * p) + p] - D[(sample * q) + q]) == 0) phi = M_PI_2/4;
    else phi = 0.5 * atan(-2 * data[(sample * p) + q] / (data[(sample * p) + p] - data[(sample * q) + q]));

    for (int i=0; i<sample; i++) {
        D[(sample * p) + i] = data[(sample * p) + i] * cos(phi) - data[(sample * q) + i] * sin(phi);
        D[(sample * i) + p] = D[(sample * p) + i];

        D[(sample * q) + i] = data[(sample * p) + i] * sin(phi) + data[(sample * q) + i] * cos(phi);
        D[(sample * i) + q] = D[(sample * q) + i];
    }
    D[(sample * p) + p] = (data[(sample * p) + p] + data[(sample * q) + q]) / 2 + ((data[(sample * p) + p] - data[(sample * q) + q]) / 2) * cos(phi) - data[(sample * p) + q] * sin(phi);
    D[(sample * q) + q] = (data[(sample * p) + p] + data[(sample * q) + q]) / 2 - ((data[(sample * p) + p] - data[(sample * q) + q]) / 2) * cos(phi) + data[(sample * p) + q] * sin(phi);

    D[(sample * p) + q] = 0;
    D[(sample * q) + p] = 0;

    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            data[(sample * i) + j] = D[(sample * i) + j];
        }
    }

    return phi;
}

void makeR(int p, int q, double phi) {
    double *RR, *RT;
    RR = (double*)malloc(sample * sample * sizeof(double));
    RT = (double*)malloc(sample * sample * sizeof(double));
    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            if (i == j) R[ (sample*i) + j ] = 1;
            else R[ (sample*i) + j ] = 0;
        }
    }

    RR[(sample * p) + p] = cos(phi);
    RR[(sample * p) + q] = sin(phi);
    RR[(sample * q) + p] = -sin(phi);
    RR[(sample * q) + q] = cos(phi);
    
    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            double tmp = 0;
            for (int m=0; m<sample; m++) {
                tmp += R[(sample * i) + j + m] * RR[(sample * (i + m)) + j];
            }
            RT[(sample * i) + j] = tmp;
        }
    }

    for (int i=0; i<sample; i++) {
        for (int j=0; j<sample; j++) {
            R[(sample * i) + j] = RT[(sample * i) + j];
        }
    }
}
