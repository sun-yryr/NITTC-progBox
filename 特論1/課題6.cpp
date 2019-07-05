#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;
void pickMRand(int original[], int subset[], int n, int m) {
    int cp_original[n];
    REP(i, n) cp_original[i] = original[i];
    REP(i, m) {
        int index = rand() % n;
        subset[i] = cp_original[index];
        n--;
        swap(cp_original[index], cp_original[n]);
    }
}

int main() {
    int a = 20;
    int b = 9;
    
    return 0;
}