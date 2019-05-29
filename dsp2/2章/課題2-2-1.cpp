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

int main() {
    vector<double> input;
    cout << "input size : ";
    int size = 4;
    double tmp;
    scanf("%d", &size);
    for(int i=0; i<size; i++) {
        scanf("%lf", &tmp);
        input.push_back(tmp);
        getchar();
    }
    vector<vector<double> > base = vector<vector<double> >(size, vector<double>(size, 0));
    vector<double> ans = vector<double>(size, 0);
    create_normal_orthogonal_base(base);
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            ans[i] += base[i][j] * input[j];
        }
    }
    REP(i,size) printf("%%lf = %lf  %%.2f = %.2f\n", ans[i], ans[i]); 
}