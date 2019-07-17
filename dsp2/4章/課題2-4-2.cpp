#include <bits/stdc++.h>
using namespace std;

#define OUT(a) cout << (a) << "\n"
#define ll long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long

const ll MOD = 10e9 + 7;
const double EPSILON = 0.0001;

/**
 *  @brief DWTをする関数
 *  @params vector<double> original: DWTする元の配列（値渡し）
 *  @params vector<double> out: DWTした後の保存する用の配列（参照渡し）
 *  @params int level: DWTするレベル
 * 
 *  @memo outはスケーリング，ウェーブレットの順で並んでいて，[lev:nのスケーリング, lev:nのウェーブレット, lev:n-1のウェーブレット, lev:n-2のウェーブレット...]といった感じに並んでいる
 */
void dwt(vector<double> original, vector<double>& out, int level) {
    // スケーリング，ウェーブレット関数
    auto scaling = [] (double a, double b) {return (1/sqrt(2))*(double)(a+b);};
    auto wavelet = [] (double a, double b) {return (1/sqrt(2))*(double)(a-b);};
    level = min(level, (int)log2(original.size()));
    int max_j = original.size();
    for(int i=0; i<level; i++) {
        max_j /= 2;
        for(int j=0; j<max_j; j++) {
            out[j] = scaling(original[2*j], original[2*j+1]);
        }
        for(int j=0; j<max_j; j++) {
            out[max_j+j] = wavelet(original[2*j], original[2*j+1]);
        }
        copy(out.begin(), out.end(), original.begin());
    }
}

int main() {
    vector<double> a{10, 6, 2, 4, 8, 2, 6, 4};
    vector<double> b(a.size());
    dwt(a, b, 3);
    printf("DWT\nbefore: ");
    for(int p=0; p<8; p++) printf("%lf ", a[p]);
    printf("\nafter: ");
    for(int p=0; p<8; p++) printf("%lf ", b[p]);
    printf("\n");
    return 0;
}