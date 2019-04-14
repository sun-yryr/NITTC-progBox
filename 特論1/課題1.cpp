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
    int a = 102;
    int b = 12;
    printf("%4d  %4d\n",a,b);
    //swap_without_address(a, b);
    //swap_in_temporary(&a, &b);
    //swap_without_temporary(&a, &b);
    swap_xor(&a, &b);
    printf("%4d  %4d\n",a,b);
    return 0;
}