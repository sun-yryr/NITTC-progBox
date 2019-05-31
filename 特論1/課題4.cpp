#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>
using namespace std;
#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
ll MOD = 10e9 + 7;

int rand7(){
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand5(1, 5);        // [0, 99] 範囲の一様乱数
    int tmp = 0;
    REP(i, 8) tmp += rand5(mt);
    if (tmp == 40) {
        tmp--;
    }
    int a = (int)tmp/7;
    return (tmp-a*7)+1;
}

int randaaaaa(){
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand5(0, 4);        // [0, 99] 範囲の一様乱数
    while(1) {
        int tmp = 5 * rand5(mt) + rand5(mt);
        if(tmp < 21) return (int)(tmp%7)+1;
    }
}

int main() {
    int ans[8] = {0};
    int ans2[8] = {0};
    int kaisu = 100000;
    REP(i,kaisu) {
        ans[rand7()]++;
    }
    for(int i=1; i<=7; i++) {
        printf("[%d] ", i);
        OUT(ans[i]/(double)kaisu);
    }
    return 0;
}