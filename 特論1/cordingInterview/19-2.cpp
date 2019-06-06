#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)
#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

ll MOD = 10e9 + 7;

/*
    見つけるアルゴリズムをデザインする。
    三目並べで勝敗が決まったことを判定する？？？？？？


    三目並べとは，3*3の格子を用意し...(wikiより)
    つまりどう転んでも8回の判定でいい
 */

bool is_won(char board[3][3]) {
    REP(i, 3) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}



int main(int argc, char const *argv[]) {
    char input[3][3] = {
        {'o', 'x', 'x'},
        {'o', 'x', 'o'},
        {'x', 'o', 'x'}
    };
    printf("%s\n", (is_won(input)?"True":"False"));
    return 0;
}
