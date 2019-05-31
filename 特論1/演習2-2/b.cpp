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

// 2の実装
int rand7_2(){
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand5(0, 4);
    int tmp = 0;
    REP(i, 2) tmp += rand5(mt);
    return tmp%7;
}

int rand_count = 0;
int func_count = 0;
int rand7_3(){
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand5(0, 4);        // [0, 99] 範囲の一様乱数
    int count = 0;
    while(1) {
        int tmp = 5 * rand5(mt) + rand5(mt);
        count += 2;
        if(tmp < 21) {
            //printf("rand5 Count = %d\n", count);
            rand_count += count;
            func_count += 1;
            return tmp%7;
        }
    }
}

int rand7_4(){
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand5(0, 4);        // [0, 99] 範囲の一様乱数
    int count = 0;
    while(1) {
        int tmp = 5 * rand5(mt) + rand5(mt);
        count += 2;
        if(tmp < 21) {
            //printf("rand5 Count = %d\n", count);
            rand_count += count;
            func_count += 1;
            int a = (int)tmp/7;
            return (tmp-a*7);
        }
    }
}

int rand15() {
    while(1) {
        int tmp = 7 * rand7_3() + rand7_3();
        if(tmp < 45) return tmp%15;
    }
}

int main() {
    int ans[16] = {0};
    int kaisu = 100000;
    REP(i,kaisu) {
        ans[rand15()]++;
    }
    REP(i, 15) {
        printf("[%2d] = %lf\n", i, ans[i]/(double)kaisu);
    }
    return 0;
}