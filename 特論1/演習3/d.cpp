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

int add_no_arithm2(int a, int b) {
    int tmp;
    do {
        tmp = a^b;
        b = (a&b) << 1;
        a = tmp;
    } while (b!=0);
    return a;
}

// 引き算
int sub_no_arithm(int a, int b) {
    b = ~b;
    b = add_no_arithm2(b, 1);
    return add_no_arithm2(a, b);
}

// 掛け算
int mlp_no_arithm(int a, int b) {
    int ans = 0;
    while(b != 0) {
        if(b & 0x1) {
            ans = add_no_arithm2(ans, a);
        }
        b >>= 1;
        a <<= 1;
    }
    return ans;
}

// 割り算 a/b
int div_no_arithm(int a, int b) {
    int count = 0;
    while(a >= b) {
        a = sub_no_arithm(a, b);
        count++;
    }
    return count;
}

// 余算 a%b
int mod_no_arithm(int a, int b) {
    while(a >= b) {
        a = sub_no_arithm(a, b);
    }
    return a;
}

int main() {
    int a = 20;
    int b = 9;
    printf("%d / %d = %d\n", a,b,div_no_arithm(a,b));
    printf("%d %% %d = %d\n", a,b,mod_no_arithm(a,b));
    return 0;
}