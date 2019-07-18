#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;
int recursive(int n) {
    if (n == 0) return 0;
    int p = 1;
    while(10*p < n) p*=10;
    int first = n/p;
    int re = n%p;
    int n2 = 0;
    if (first > 2) n2 += p;
    else if (first == 2) n2 += re + 1;
    int n2o = first * recursive(p-1) + recursive(re);
    return n2 + n2o;
}

int iterat(int n) {
    int count = 0, digit = 0, num = n, seendigits = 0, position = 0, pow10 = 1;
    while(num > 0) {
        digit = num % 10;
        int pow10_pos = pow10 / 10;
        count += digit * position * pow10_pos;
        if (digit == 2) count += seendigits + 1;
        else if (digit > 2) count += pow10;
        seendigits = seendigits + pow10 * digit;
        pow10 *= 10;
        position++;
        num /= 10;
    }
    return count;
}

int main() {
    int n = 90;
    cout << recursive(n) << endl;
    cout << iterat(n) << endl;
    return 0;
}