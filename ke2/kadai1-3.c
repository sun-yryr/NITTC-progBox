#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 196

double A[N][N], B[N][N], C[N][N], R[N][N], RR[N][N];
double qri = 0.01; //収束条件

void getAbsolute(double[N][N], int[2]);
double getabs(double[N][N]);
void createIdentity(double[N][N]);
double elim(double[N][N], int, int);
void makeR(int, int, double);


int main() {
    char filename[256];
    int i, j;
    FILE *fp;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) RR[i][i] = 1;
            else RR[i][j] = 0;
        }
    }

    for (int out=1; out<=47; out++) {
        snprintf(filename, 256, "./dispersion/sigma%02d.txt", out);
        printf("read[%s]\n", filename);
        if ((fp = fopen(filename, "r")) == NULL) {
            printf("read_file open error.\n");
            exit(EXIT_FAILURE);
        }
        /* ファイルから読み込み -> A, B */
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                fscanf(fp, "%lf¥n", &A[i][j]);
                B[i][j] = A[i][j];
                //printf("%lf, %lf\n", A[(sample * i) + j], B[(sample * i) + j]);
            }
        }
        fclose(fp);
        /* ---------------------------------------------------- */
        int step = 0;
        int index[2];
        int p, q;
        double phi;

        createIdentity(R);
        double non_diag_max = getabs(B);
        while(non_diag_max >= qri) {
            step++;
            getAbsolute(B, index);
            p = index[0];
            q = index[1];
            //printf("%d, %d     %lf\n", p, q, B[(sample * p) + q]);
            phi = elim(B, p, q);
            makeR(p, q, phi);
            non_diag_max = getabs(B);
            printf("step=%d   dig_max=%lf\n", step, non_diag_max);
        }
        /* ----------------------------------------------------- */
        printf("step=%d   dig_max=%lf\n", step, non_diag_max);
        snprintf(filename, 256, "./jacobi/data%02d.txt", out);
        if ((fp = fopen(filename, "w")) == NULL) {
            printf("write_file open error.\n");
            exit(EXIT_FAILURE);
        }
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                fprintf(fp, "%lf\n", R[i][j]);
            }
        }
    fclose(fp);
    }

    return 0;
}

double getabs(double data[N][N]) {
    double max = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) C[i][i] = 0;
            else C[i][j] = fabs(data[i][j]);

            if (C[i][j] > max) max = C[i][j];
        }
    }
    return max;
}


/* 
    非対角成分の絶対値の最大値の添字を返却する
    返り値は[i, j]
*/
void getAbsolute(double data[N][N], int out[2]) {
    int i,j;
    double max = 0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (i == j) C[i][i] = 0;
            else C[i][j] = fabs(data[i][j]);
            
            if (C[i][j] > max) {
                max = C[i][j];
                out[0] = i;
                out[1] = j;
            }
        }
    }
}

void createIdentity(double data[N][N]) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) data[i][j] = 1;
            else data[i][j] = 0;
        }
    }
}

double elim(double data[N][N], int p, int q) {
    double D[N][N];
    double phi;

    if ((data[p][p] - data[q][q]) == 0) phi = M_PI_2/4;
    else phi = 0.5 * atan(-2 * data[p][q] / (data[p][p] - data[q][q]));

    for (int i=0; i<N; i++) {
        D[p][i] = data[p][i] * cos(phi) - data[q][i] * sin(phi);
        D[i][p] = D[p][i];

        D[q][i] = data[p][i] * sin(phi) + data[q][i] * cos(phi);
        D[i][q] = D[q][i];
    }
    D[p][p] = (data[p][p] + data[q][q]) / 2 + ((data[p][p] - data[q][q]) / 2) * cos(phi) - data[p][q] * sin(phi);
    D[q][q] = (data[p][p] + data[q][q]) / 2 - ((data[p][p] - data[q][q]) / 2) * cos(phi) + data[p][q] * sin(phi);

    D[p][q] = 0;
    D[q][p] = 0;

    for (int i=0; i<N; i++) {
        data[p][i] = D[p][i];
        data[i][p] = D[p][i];
        data[q][i] = D[q][i];
        data[i][q] = D[q][i];
    }
    data[p][p] = D[p][p];
    data[q][q] = D[q][q];
    data[p][q] = 0;
    data[q][p] = 0;
    return phi;
}

void makeR(int p, int q, double phi) {
    double RT[N][N];
    RR[p][p] = cos(phi);
    RR[p][q] = sin(phi);
    RR[q][p] = -sin(phi);
    RR[q][q] = cos(phi);
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            double tmp = 0;
            for (int m=0; m<N; m++) {
                tmp += R[i][m] * RR[m][j];
            }
            RT[i][j] = tmp;
        }
    }

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            R[i][j] = RT[i][j];
        }
    }
}
