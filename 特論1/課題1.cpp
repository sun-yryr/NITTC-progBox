#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n";
#define ll long long
ll MOD = 10e9 + 7;

void swap_without_address(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap_in_temporary(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_without_temporary(int *a, int *b) {
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap_xor(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}


int main() {
    chrono::system_clock::time_point start, end;
    double time;
    int a = 102;
    int b = 32546;
    printf("               %5d  %5d\n",a,b);
/*
    start = chrono::system_clock::now();
    swap_without_address(a, b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("%5d  %5d  処理時間 : %lf\n",a,b,time);
*/

    start = chrono::system_clock::now();
    REP(i, 10000) swap_in_temporary(&a, &b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("nomal          %5d  %5d  処理時間 : %lf\n",a,b,time);

    start = chrono::system_clock::now();
    REP(i, 10000) swap_without_temporary(&a, &b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("without temp   %5d  %5d  処理時間 : %lf\n",a,b,time);

    start = chrono::system_clock::now();
    REP(i, 10000) swap_xor(&a, &b);
    end = chrono::system_clock::now();
    time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("xor            %5d  %5d  処理時間 : %lf\n",a,b,time);
    return 0;
}