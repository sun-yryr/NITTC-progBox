#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n";
#define ll long long
ll MOD = 10e9 + 7;

int maximum_ifelse(int a, int b) {
    return a>b?a:b;
}

int maximum(int a, int b) {
    int c = a-b;
    int k = (c>>31)&1;
    return a-k*c;
}

int minimum(int a, int b) {
    int c = a-b;
    int k = (c>>31)&1;
    return b+k*c;
}

int main() {
    int a,b;
    cin >> a >> b;
    //OUT(maximum_ifelse(a,b));
    //OUT(maximum(a,b));
    //OUT(minimum(a,b));
    return 0;
}