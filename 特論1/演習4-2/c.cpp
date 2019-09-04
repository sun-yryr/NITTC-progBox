#include <bits/stdc++.h>
#include <istream>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

int a(vector<int> n) {
    int count = 0;
    int size = n.size();
    for(int i=0; i<size; i++) {
        if (n[i] == 0) count += 1;
        else count += (int)(log10(n[i]))+1;
    }
    return count;
}
int a(int n) {
    if (n == 0) return 1;
    return (int)(log10(n))+1;
}

int main() {
    int n;
    cin >> n;
    cout << a(n) << endl;
    return 0;
}