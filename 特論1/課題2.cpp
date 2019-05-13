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

/* 課題2-B
if-else等の比較演算子を使わずに3つの数値の最大値，最小値，中央値を出力するアルゴリズムを実装する */
int findMax(int a, int b, int c) {
    a = a - ((a - b) & ((a - b) >> 31));
    return a - ((a - c) & ((a - c) >> 31));
}
int findMin(int a, int b, int c) {
    b = b + ((a - b) & ((a - b) >> 31));
    return b + ((c - b) & ((c - b) >> 31));
}
int findMid(int a, int b, int c) {
    return a+b+c-findMax(a,b,c)-findMin(a,b,c);
}

/* 課題2-C 比較演算子あり
N個の数字から最大または最小値を出力する関数をかけ（関数利用は1回のみ）*/
int findMax_fromlist(int a[], int n) {
    int tmp_max = a[0];
    for(int i=1; i<n; i++) {
        tmp_max = tmp_max - ((tmp_max - a[i]) & ((tmp_max - a[i]) >> 31));
    }
    return tmp_max;
}
int findMin_fromlist(int a[], int n) {
    int tmp_min = a[0];
    for(int i=1; i<n; i++) {
        tmp_min = tmp_min + ((a[i] - tmp_min) & ((a[i] - tmp_min) >> 31));
    }
    return tmp_min;
}

int main() {
    chrono::system_clock::time_point start, end;
    double time;
    int a,b,c;
    cin >> a >> b;
    printf("課題2 : 実行時間の計測（繰り返し10001回）\n");
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

    int s[10] = {1,5,2,7,3,12,5,6,2,5};
    OUT(findMin_fromlist(s, 10));
    return 0;
}