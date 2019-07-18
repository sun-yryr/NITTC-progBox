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
    int nnn = n;
    REP(i, n) cp_original[i] = original[i];
    for(int i=0; i<n; i++) printf("%d ", cp_original[i]);
    printf("\n");
    REP(i, m) {
        int index = rand() % n;
        subset[i] = cp_original[index];
        n--;
        swap(cp_original[index], cp_original[n]);
        for(int i=0; i<nnn; i++) printf("%d ", cp_original[i]);
        printf("\n");
    }
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[6], c[6];
    pickMRand(a, c, 9, 6);
    return 0;
}