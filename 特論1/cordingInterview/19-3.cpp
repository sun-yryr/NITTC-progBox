#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <numeric>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

/*
    nの階乗をsとした時に，sの末尾の0の数を計算するアルゴリズムをかく

    example : n = 5 -> 1 (5! == 120より)

    解法 : 末尾の0の数は階乗内に出てくる10の個数である。
        つまり10の個数であり，5の個数である。（2は5より多いので関係ない）
        Sigma(N/5^k)で求められる。(1<=k<log5(N))
 */


ll count_factorial_trailing_zero(int n) {
    vector<ll> five;
    int max_k = static_cast<int>(log(n)/log(5));
    for(int k=1; k<=max_k; k++) five.push_back(k);
    auto five_quantity = vector<ll>(five.size());
    transform(five.begin(), five.end(), five_quantity.begin(), [&n](ll x){
        return static_cast<int>(n/pow(5, x));
    });
    ll count_zero = accumulate(five_quantity.begin(), five_quantity.end(), (ll)0, [](ll a, ll b){return a+b;});
    return count_zero;
}


int main(int argc, char const *argv[]) {
    printf("N = ");
    int n;
    cin >> n;
    printf("末尾の0は%lld個です\n", count_factorial_trailing_zero(n));
    return 0;
}
