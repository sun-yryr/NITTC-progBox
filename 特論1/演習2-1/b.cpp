#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
#include <numeric>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
ll MOD = 10e9 + 7;

int total_product(vector<int> a, int s, int e) {
    int p = 1;
    for(int i=s; i<=e; i++) {
        p *= a[i];
    }
    return p;
}
int find_index(vector<int> a, int s, int e, int value) {
    for(int i=s; i<=e; i++) {
        if(a[i] == value) {
            return i;
        }
    }
    return -1;
}

int findMPP(vector<int> a) {
    printf("input : {");
    int n = a.size();
    int maxp = 0, p=1;
    for(int i=0; i<n; i++) {
        printf("%d ", a[i]);
        if (a[i] == 0) p = 1;
        else {
            p *= a[i];
            if (maxp < p) maxp = p;
            else if (maxp < a[i]) maxp = a[i];
        }
    }
    printf("}\n");
    printf("output : %d\n", maxp);
    return maxp;
}

int main() {
    /* この数列の場合、部分列の最大積は{3,-2,-4,10}で240 */
    int a[] = {2, -3, 3, -2, -4, 10};
    int a2[] = {-3, 6, 8, -1, 2, 0, 2, -3, 3, -2, -4, 10};
    vector<int> t(a, end(a));
    findMPP(t);
    return 0;
}