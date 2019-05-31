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
    int size = 4;

}