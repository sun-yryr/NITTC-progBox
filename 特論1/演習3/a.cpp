#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

// 足し算
int add_no_arithm(int a, int b) {
    if (b==0) return a;
    int sum = a^b;
    int carry = (a&b) << 1;
    return add_no_arithm(sum, carry);
}

template<typename T>
T add_no_arithm2(T a, T b) {
    int tmp;
    do {
        tmp = a^b;
        b = (a&b) << 1;
        a = tmp;
    } while (b!=0);
    return a;
}

int main() {
    double a = 35.5;
    double b = 19;
    printf("%f + %f = %d\n", a,b,add_no_arithm2(a,b));
    return 0;
}