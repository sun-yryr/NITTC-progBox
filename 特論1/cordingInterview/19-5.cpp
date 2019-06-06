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
    マスターマインドゲームは以下のようにプレイされます。
    コンピュータには、赤（R）、黄色（Y）、緑（G）、または青（B）のボールが入った4つのスロットがあります。
    たとえば、コンピュータにはRGGBがあります（スロット＃1が赤、スロット＃2と＃3は緑色、スロット＃4は青色です。)
    あなたは、ユーザーは、あなたが解決策を推測しようとしていますあなたは、例えばYRGBを推測するかもしれません
    正しいスロットの正しい色を推測すると、「ヒット」します。存在しているが間違ったスロットにある色を推測すると、「擬似ヒット」が表示されます。 疑似ヒット
    推測ごとに、ヒット数と疑似ヒット数が表示されます。
    推測と解が与えられたときに、ヒット数と疑似ヒット数を返すメソッドを作成します。
 */

// first -> ヒット数
// second -> 擬似ヒット数
pair<int, int> Hits(char ans[4], char select[4]) {
    pair<int, int> a = make_pair(0, 0);
    REP(i, 4) {
        if(ans[i] == select[i]) a.first++;
        for(int j=i+1; j<4; j++) {
            if(ans[i] == select[j]) a.second++;
        }
    }
    return a;
}


int main(int argc, char const *argv[]) {
    char *a = "YRGB";
    char *b = "YRBB";
    pair<int, int> ans = Hits(a, b);
    cout << "Hit : " << ans.first << endl;
    cout << "Bite : " << ans.second << endl;
    return 0;
}
