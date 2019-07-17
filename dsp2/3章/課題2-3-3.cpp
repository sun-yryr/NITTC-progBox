#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

const ll MOD = 10e9 + 7;
const double EPSILON = 0.0001;

void matrix_product(vector<vector<double> > &a, vector<double> &b, vector<double> &ans) {
    int row = 3;
    for(int i=0; i<row; i++) {
        ans[i] = 0;
        for(int j=0; j<row; j++) {
            ans[i] += a[i][j] * b[j];
        }
    }
}

double eigen_value(vector<double> a, vector<double> b) {
    double ans = 0;
    double tmp = 0;
    int size = a.size();
    for(int i=0; i<size; i++) {
        ans += a[i] * b[i];
    }
    return ans;
}

void matrix_normalization(vector<double> &a) {
    double tmp = 0;
    int size = a.size();
    for(int i=0; i<size; i++) {
        tmp += a[i] * a[i];
    }
    tmp = sqrt(tmp);
    for(int i=0; i<size; i++) {
        a[i] /= tmp;
    }
}

double matrix_norme(vector<double> a, vector<double> b) {
    double tmp = 0;
    int size = a.size();
    for(int i=0; i<size; i++) {
        a[i] -= b[i];
    }
    for(int i=0; i<size; i++) {
        tmp += a[i] * a[i];
    }
    return sqrt(tmp);
}

double a(vector<vector<double> > original, vector<double>& v) {
    const int ROW = original.size();
    const int COLUMN = original.front().size();
    vector<double> v_hat{0,0,0};
    vector<double> v_old{0,0,0};
    double lambda = 0;
    double error = 10000;
    do{
        matrix_product(original, v, v_hat);
        lambda = eigen_value(v_hat, v);
        v_old = v;
        matrix_normalization(v_hat);
        v = v_hat;
        error = matrix_norme(v, v_old);
    } while(error >= EPSILON);
    OUT("固有値");
    printf("%f\n", lambda);
    OUT("固有ベクトル");
    REP(i, 3) printf("%f ", v[i]);
    printf("\n");
    return lambda;
}

int main(int argc, char const *argv[]) {
    vector<vector<double> > original{
        {2,1,3},
        {1,2,3},
        {3,3,20}
    };
    double la, tmp;
    vector<double> v{1,0,0};
    for(int i=0; i<3; i++) {
        la = a(original, v);
        for(int k=0; k<3; k++) {
            for(int p=0; p<3; p++) {
                original[k][p] -= la * v[k] * v[p];
            }
        }
    }
    return 0;
}
