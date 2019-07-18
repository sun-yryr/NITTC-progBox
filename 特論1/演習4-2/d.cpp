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