#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
ll MOD = 10e9 + 7;

int findMSS(vector<int> a) {
    int n = a.size();
    int maxSum = a[0];
    int sum = a[0];
    for(int i=1; i<n; i++) {
        sum += a[i];
        if(sum < 0) sum = 0;
        if(maxSum < sum) maxSum = sum;
    }
    return maxSum;
}

/* 負数が偶数になり、0が含まれない部分列を求める。-> pair
積の最大値を求めて返す*/
int dp[100000];
int findMPP_fix(vector<int> a) {
    int n = a.size();
    vector<pair<int, int> > partial_array;

}





int findMPP(vector<int> a) {
    int n = a.size();
    int maxp = 0, p=1;
    for(int i=0; i<n; i++) {
        if (a[i] == 0) p = 1;
        else {
            p *= a[i];
            if (maxp < p) maxp = p;
            else if (maxp < a[i]) maxp = a[i];
        }
    }
    return maxp;
}

int main() {
    /* この数列の場合、部分列の最大積は{3,-2,-4,10}で240 */
    int a[] = {2, -3, 3, -2, -4, 10};
    vector<int> t(a, end(a));
    OUT(findMPP(t));
    return 0;
}