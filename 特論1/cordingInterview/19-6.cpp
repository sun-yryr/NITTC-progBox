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
    0から999999が与えられるので，英語表記に変換して返す

    うーん and どうしよう
 */

string change_english_one(int num) {
    switch (num) {
        case 1:
            return "one";
            break;
        case 2:
            return "two";
            break;
        case 3:
            return "three";
            break;
        case 4:
            return "four";
            break;
        case 5:
            return "five";
            break;
        case 6:
            return "six";
            break;
        case 7:
            return "seven";
            break;
        case 8:
            return "eight";
            break;
        case 9:
            return "nine";
            break;
        default:
            return "";
            break;
    }
}

string change_english(int num) {
    int ten_place = static_cast<int>(num/10);
    int one_place = num%10;
    switch (ten_place) {
        case 0:
            return change_english_one(one_place);
            break;
        case 1:
            switch (one_place) {
                case 0:
                    return "ten";
                    break;
                case 1:
                    return "eleven";
                    break;
                case 2:
                    /* code */
                    return "twelve";
                    break;
                case 3:
                    /* code */
                    return "thirteen";
                    break;
                case 4:
                    /* code */
                    return "fourteen";
                    break;
                case 5:
                    /* code */
                    return "fifteen";
                    break;
                case 6:
                    /* code */
                    return "sixteen";
                    break;
                case 7:
                    /* code */
                    return "seventeen";
                    break;
                case 8:
                    /* code */
                    return "eighteen";
                    break;
                case 9:
                    /* code */
                    return "nineteen";
                    break;
                }
            break;
        case 2:
            return "twenty " + change_english_one(one_place);
            break;
        case 3:
            return "thirty " + change_english_one(one_place);
            break;
        case 4:
            return "forty " + change_english_one(one_place);
            break;
        case 5:
            return "fifty " + change_english_one(one_place);
            break;
        case 6:
            return "sixty " + change_english_one(one_place);
            break;
        case 7:
            return "seventy " + change_english_one(one_place);
            break;
        case 8:
            return "eighty " + change_english_one(one_place);
            break;
        case 9:
            return "ninety " + change_english_one(one_place);
            break;
    }
    return "";
}

vector<string> transform_english_number(int num) {
    vector<string> ans;
    int digit = static_cast<int>(log10(num)) +1;
    if(digit == 6) {
        int tmp = static_cast<int>(num/100000);
        ans.push_back(change_english(tmp) + " hundred ");
        num -= tmp*100000;
        digit = static_cast<int>(log10(num)) +1;
    }
    if(3 < digit) {
        int tmp = static_cast<int>(num/1000);
        ans.push_back(change_english(tmp) + " thousand ");
        num -= tmp*1000;
        digit = static_cast<int>(log10(num)) +1;
    }
    if(digit == 3) {
        int tmp = static_cast<int>(num/100);
        ans.push_back(change_english(tmp) + " hundred ");
        num -= tmp*100;
        digit = static_cast<int>(log10(num)) +1;
    }
    if(1 <= digit) ans.push_back(change_english(num));
    return ans;
}

int main(int argc, char const *argv[]) {
    printf("num = ");
    int n;
    cin >> n;
    vector<string> ans = transform_english_number(n);
    //ans.insert(ans.end()-1, "and ");
    REP(i, ans.size()) {
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
