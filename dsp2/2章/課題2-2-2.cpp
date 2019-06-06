#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
ll MOD = 10e9 + 7;

void create_normal_orthogonal_base(vector<vector<double> >& base) {
    int max_rc = base.size();
    double tmp;
    for(int i=0; i<max_rc; i++) {
        for(int j=0; j<max_rc; j++) {
            if (i==0) base[i][j] = 1/sqrt(max_rc);
            else {
                tmp = cos(((2.0*j+1)*i*M_PI)/(double)(2.0*max_rc));
                base[i][j] = sqrt(2.0/(double)max_rc) * tmp;
            }
        }
    }
    OUT("直交基底");
    REP(i,max_rc) {
        REP(j, max_rc) {
            printf("%lf ", base[i][j]);
        }
        cout << "\n";
    }
    OUT("---------");
}

void transposed_matrix(vector<vector<double> >& matrix) {
    int n = matrix.size();
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

int main() {
    int size = 4;
    double tmp;
    scanf("%d", &size);
    vector<vector<double> > input = vector<vector<double> >(size, vector<double>(size, 0));
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            scanf("%lf", &input[i][j]);
            getchar();
        }
    }
    vector<vector<double> > base = vector<vector<double> >(size, vector<double>(size, 0));
    vector<vector<double> > base2 = vector<vector<double> >(size, vector<double>(size, 0));
    vector<vector<double> > aaa = vector<vector<double> >(size, vector<double>(size, 0));
    vector<vector<double> > ans = vector<vector<double> >(size, vector<double>(size, 0));
    create_normal_orthogonal_base(base);
    create_normal_orthogonal_base(base2);
    transposed_matrix(base2);
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            for(int k=0; k<size; k++) {
                aaa[i][j] += base[i][k] * input[k][j];
            }
        }
    }for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            for(int k=0; k<size; k++) {
                ans[i][j] += aaa[i][k] * base2[k][j];
            }
        }
    }
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%lf ", ans[i][j]);
        }
        printf("\n");
    }
}