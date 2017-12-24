#include <stdio.h>
#include <string.h>

#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    /* 講義資料を参考に実装せよ */
    int i = 0,j = 0,count = 0;
    int text_len = strlen(text);
    int pat_len = strlen(pattern);
    if (text_len < pat_len) {
        printf("patternが大きすぎます.");
        return -1;
    }
    while ( i < text_len && j < pat_len ) {
        if (text[i] == pattern[j]) {
            if (count==0)count = i;
            printf("%c",pattern[j]);
            i++,j++;
        }
        else {
            printf("%c",pattern[j]);
            if (count!=0)i=count,count = 0;
            printf("   ...failure\n");
            for (int p=0;p<=i;p++) printf(" ");
            i++;
            j=0;
        }
    }
    if (j == pat_len) {
        printf("   ...success\n");
        return count;
    }
    else return -1;
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
    /* 講義資料を参考に実装せよ */
    int j,k,m;
    int pat_len = strlen(pattern);
    
    for ( j = 0; j < pat_len; j++ ) {
        if ( j < 1 )
            next[j] = 1;
        else {
            for ( k = 1; k < j; k++ ) {
                for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ ) ;
                if ( m == j )
                    break;
            }
            next[j] = k;
        }
    }
    
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
    /* 講義資料を参考に実装せよ */
    int i = 0,j = 0;
    int text_len = strlen(text);
    int pat_len = strlen(pattern);
    if (text_len < pat_len) {
        printf("patternが大きすぎます.");
        return -1;
    }
    /* テキストの最後尾に行き当たるか、パターンが見つかるまで繰り返す */
    while ( i < text_len && j < pat_len ) {
        if (text[i] == pattern[j]) {
            printf("%c",pattern[j]);
            i++,j++;
        }
        else {
            printf("%c",pattern[j]);
            printf("   ...failure\n");
            j = j -next[j];
            if (j < 0) i++,j++;
            for (int p=0;p<i;p++) printf(" ");
        }
    }
    if (j == pat_len) {
        printf("   ...success\n");
        return i-pat_len;
    }
    else return -1;
}

int main(void)
{
    char text0[TEXT_LENGTH+1];
    char pattern0[PATN_LENGTH+1];
    char text1[TEXT_LENGTH+1];
    char pattern1[PATN_LENGTH+1];
    
    int position;
    strcpy(text0,"xxxtartartayx");
    strcpy(pattern0,"tartay");
    strcpy(text1,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
    strcpy(pattern1,"pyokopyokomu");
    
    int pat_len0 = strlen(pattern0);
    int pat_len1 = strlen(pattern1);
    
#if BF
    printf("--- B F ---\n");
    printf("%s\n",text0);
    position = brute_force_search(text0, pattern0);
    printf("position=%d\n",position);
    printf("\n");
    position = 0;
    printf("%s\n",text1);
    position = brute_force_search(text1, pattern1);
    printf("position=%d\n",position);
#endif
    
#if KMP
    printf("--- KMP ---\n");
    init_next(pattern0);
    for (int i=0; i<pat_len0; i++) {
        printf("%c:next[%2d] = %2d\n",pattern0[i],i,next[i]);
    }
    printf("%s\n",text0);
    position = kmp_search(text0, pattern0);
    printf("position=%d\n",position);
    printf("\n");
    position = 0;
    init_next(pattern1);
    for (int i=0; i<pat_len1; i++) {
        printf("%c:next[%2d] = %2d\n",pattern1[i],i,next[i]);
    }
    printf("%s\n",text1);
    position = kmp_search(text1, pattern1);
    printf("position=%d\n",position);
#endif
    return 0;
}

/*実行結果（貼り付けたら空白が削除されました）
 --- B F ---
 xxxtartartayx
 t   ...failure
 t   ...failure
 t   ...failure
 tartay   ...failure
 t   ...failure
 t   ...failure
 tartay   ...success
 position=6
 
 pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
 pyokopyokomu   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokop   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokopyokomu   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokop   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokopyokom   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokopyokom   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 p   ...failure
 pyokopyokomu   ...success
 position=34
 --- KMP ---
 t:next[ 0] =  1
 a:next[ 1] =  1
 r:next[ 2] =  2
 t:next[ 3] =  3
 a:next[ 4] =  3
 y:next[ 5] =  3
 xxxtartartayx
 t   ...failure
 t   ...failure
 t   ...failure
 tartay   ...failure
 rtay   ...success
 position=6
 
 p:next[ 0] =  1
 y:next[ 1] =  1
 o:next[ 2] =  2
 k:next[ 3] =  3
 o:next[ 4] =  4
 p:next[ 5] =  5
 y:next[ 6] =  5
 o:next[ 7] =  5
 k:next[ 8] =  5
 o:next[ 9] =  5
 m:next[10] =  5
 u:next[11] = 11
 pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
 pyokopyokomu   ...failure
 p   ...failure
 pyokopyokomu   ...failure
 p   ...failure
 pyokopyokom   ...failure
 pyokom   ...failure
 pyokomu   ...success
 position=34
*/
