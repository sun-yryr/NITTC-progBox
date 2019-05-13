#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
ll MOD = 10e9 + 7;

int maximum_ifelse(int a, int b) {
    if(a > b) return a;
    else return b;
}

int maximum_ternary(int a, int b) {
    return a>b?a:b;
}

int maximum_without_ifelse(int a, int b) {
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
    chrono::system_clock::time_point start, end;
    double time;
    int a,b,c;
    cin >> a >> b;
    start = chrono::system_clock::now();
    REP(i, 10000) c = maximum_ifelse(a,b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("if-else      %lf\n", time);

    start = chrono::system_clock::now();
    REP(i, 10000) c = maximum_ternary(a, b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("三項演算子     %lf\n", time);

    start = chrono::system_clock::now();
    REP(i, 10000) c = maximum_without_ifelse(a,b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("比較演算子なし  %lf\n", time);


    OUT(minimum(a,b));
    return 0;
}