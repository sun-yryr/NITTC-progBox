#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

char number = '4';
int adder(int n) {
    int counter = 0;
    auto f = [&] (string s) -> bool {
        return (count(s.begin(), s.end(), number) > 0);
    };
    for(int i=1; i<=n; i++) {
        if (f(to_string(i))) counter += i;
    }
    return counter;
}

int multi(int n) {
    int counter = 1;
    auto f = [&] (string s) -> bool {
        return (count(s.begin(), s.end(), number) > 0);
    };
    for(int i=1; i<=n; i++) {
        if (f(to_string(i))) counter *= i;
    }
    return counter;
}

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    cout << adder(n) << endl;
    return 0;
}