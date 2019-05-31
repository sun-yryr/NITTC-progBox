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


/* 0のない部分列を作成
   dpに負の数があるので偶数になる最大範囲を出す（高々2つ）
   見つけた範囲の最大積を返す
   再帰するたびにNが分裂するのでO(N)だと思う（どうだろう）（これは嘘、N以上あるはず）
*/
int dp[100000];
int findMPP_fix(vector<int> a, int start, int end) {
    int n = a.size();
    int zero_index = find_index(a, start, end, 0);
    if (zero_index == -1) {
        int end_point = end;
        int start_point = start;
        // 負の数が偶数ならそのまま
        if ((dp[end_point]-dp[start_point])%2 == 0 || dp[end_point]%2 == 0) return total_product(a, start_point, end_point);
        else {
            int start_point_left = start_point,
                start_point_right = 0,
                end_point_left = 0,
                end_point_right = end_point;
            // SPRを探す
            for(int i=end_point-1; i>=start_point; i--) {
                if (dp[i] == 1) {
                    start_point_right = i;
                    break;
                }
            }
            // EPLを探す
            for(int i=end_point-1; i>=start_point; i--) {
                if(dp[i] == dp[end_point]-1) {
                    end_point_left = i;
                    break;
                }
            }
            // maxを返す
            int w1 = total_product(a, start_point_left, end_point_left);
            int w2 = total_product(a, start_point_right, end_point_right);
            return max(w1, w2);
        }
    } else {
        return max(findMPP_fix(a, start, zero_index-1), findMPP_fix(a, zero_index+1, end));
    }
}

int main() {
    /* この数列の場合、部分列の最大積は{3,-2,-4,10}で240 */
    int a[] = {2, -3, 3, -2, -4, 10};
    int a2[] = {-3, 6, 8, -1, 2, 0, 2, -3, 3, -2, -4, 10};
    vector<int> t(a, end(a));
    // 負の数の累積和テーブルを作っておく
    printf("input : {%d ", t[0]);
    if(t[0] < 0) dp[0] = 1;
    for(int i=1; i<t.size(); i++) {
        printf("%d ", a[i]);
        if(t[i] == 0) dp[i] = 0;
        else if(t[i] < 0) dp[i] = dp[i-1] + 1;
        else dp[i] = dp[i-1];
    }
    printf("}\n");
    printf("output : %d\n", findMPP_fix(t, 0, t.size()-1));
    return 0;
}