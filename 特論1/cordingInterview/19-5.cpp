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


    example : コンピュータ「YYYY」　ユーザ「GYBR」
              ここで，正解が1,3なのか，1,0なのかが気になる。このコードは1,0を出力するように組んだ。
 */

// first -> ヒット数
// second -> 擬似ヒット数
// O(N^2) 愚直解
pair<int, int> Hits(string ans, string select) {
    pair<int, int> a = make_pair(0, 0);
    if (ans.size() != select.size()) return a;
    int N = ans.size();
    REP(i, N) {
        if(ans[i] == select[i]) {
            a.first++;
            ans[i] = '#';
            select[i] = '.';
        }
    }
    REP(i, N) REP(j, N) {
        if (ans[j] == select[i]) {
            a.second++;
            ans[j] = '#';
            select[i] = '.';
        }
    }
    return a;
}

// O(N) いいぞ
pair<int, int> Hits_N_ron(string ans, string select) {
    pair<int, int> a = make_pair(0, 0);
    if (ans.size() != select.size()) return a;
    int N = ans.size();
    char ball[] = {'R', 'Y', 'G', 'B'};
    int count_ans[4] = {0, 0, 0, 0}; // R, Y, G, B
    int count_select[4] = {0, 0, 0, 0}; //R, T, G, B
    REP(i, N) {
        if (ans[i] == select[i]) ++a.first;
        else {
            REP(j, 4) {
                if (ans[i] == ball[j]) ++count_ans[j];
                if (select[i] == ball[j]) ++count_select[j];
            }
        }
    }
    REP(i, 4) {
        a.second += min(count_ans[i], count_select[i]);
    }
    return a;
}


int main(int argc, char const *argv[]) {
    string a = "YRGBG";
    string b = "GRYYY";
    pair<int, int> ans = Hits_N_ron(a, b);
    cout << "Hit : " << ans.first << endl;
    cout << "Bite : " << ans.second << endl;
    ans = Hits(a, b);
    cout << "Hit : " << ans.first << endl;
    cout << "Bite : " << ans.second << endl;
    return 0;
}
