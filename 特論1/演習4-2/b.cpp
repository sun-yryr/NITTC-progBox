#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

int number = 4;
int recursive(int n) {
    if (n == 0) return 0;
    int p = 1;
    while(10*p < n) p*=10;
    int first = n/p;
    int re = n%p;
    int n2 = 0;
    if (first > number) n2 += p;
    else if (first == number) n2 += re + 1;
    int n2o = first * recursive(p-1) + recursive(re);
    return n2 + n2o;
}

int main() {
    int n;
    cout << "数える数字 : ";
    cin >> number;
    cout << "n = ";
    cin >> n;
    cout << recursive(n) << endl;
    return 0;
}