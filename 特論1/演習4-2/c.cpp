#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

int a(int n) {
    int count = 0;
    for(int i=1; i<=n; i++) {
        count += (int)(log10(i))+1;
    }
    return count+1;
}

int main() {
    int n;
    cin >> n;
    cout << a(n) << endl;
    return 0;
}