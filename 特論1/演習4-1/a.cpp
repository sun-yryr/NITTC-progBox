#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;
void pickRand(int original[], int subset[], int n, int m) {
    for(int i=0; i<m; i++) {
        int index = (int)(rand() % n);
        subset[i] = original[index];
    }
}

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
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[6], c[6];
    pickRand(a, b, 9, 6);
    printf("2.\n");
    for(int i=0; i<6; i++) printf("%d ", b[i]);
    printf("\n4.\n");
    pickMRand(a, c, 9, 6);
    for(int i=0; i<6; i++) printf("%d ", c[i]);
    printf("\n");
    return 0;
}