#include <stdio.h>
#include <string.h>
#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 5
int next[PATN_LENGTH];
/* テキストとパターンの不一致が見つかったときにどれだけずらすかを示す表 */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* 二つの数a,bのうち大きい方を返すマクロ */

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    /* 前回実装済み */
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
    /* 前回実装済み */
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
    /* 前回実装済み */
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


/* BM法用のずらし表を作成する */
void init_skip(uchar pattern[])
{
    int i = 0;
    int patn_len = strlen(pattern);
    /* 講義資料を参考に実装せよ */
    for( i = 0; i < PATN_LENGTH; i++ ){
        skip[i] = patn_len;
    }
    for( i = 0; i < patn_len; i++ ){
        skip[pattern[i]] = patn_len - i - 1;
    }
    for( i = 0; i < patn_len; i++ ){
        printf("%c: skip[%3d] = %d\n",pattern[i],pattern[i],skip[pattern[i]]);
    }
    
}


/* 文字列textから文字列patternを検索する(BM法) */
int bm_search(uchar text[], uchar pattern[]) {
    
    /* 講義資料を参考に実装せよ */
    int i; /* 注目しているテキストの位置 */
    int j; /* 注目しているパターンの位置 */
    int text_len, patn_len;
    int cou = 0;
    
    text_len = strlen(text);    /* テキストの長さをセット */
    patn_len = strlen(pattern); /* パターンの長さをセット */
    
    i = patn_len -1;
    
    while( i < text_len ) {
        j = patn_len -1;
        for (cou=0; cou<i; cou++) {
            printf(">");
        }
        while( text[i] == pattern[j] ) {
            if (j == 0) {
                printf("%c  ... success\n",pattern[j]);
                return i;
            }else {
                printf("%c\n",pattern[j]);
                i--,j--;
                for (cou=0; cou<i; cou++) {
                    printf(" ");
                }
            }
        }
        printf("%c  ...failure\n",pattern[j]);
        i = i + max(skip[text[i]],patn_len-j);
    }
    return -1;
    
}


int main(void)
{
    uchar text[TEXT_LENGTH+1];
    uchar pattern[PATN_LENGTH+1];
    int position;
    strcpy(text,"aabbabcabc");
    strcpy(pattern,"abcab");
    
#if BF
    printf("--- B F ---\n");
    printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
#endif
    
#if KMP
    printf("--- KMP ---\n");
    init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
#endif
    
    
#if BM
    printf("--- B M ---\n");
    init_skip(pattern);
    printf("%s\n",text);
    position = bm_search(text, pattern);
    printf("position=%d\n",position);
#endif
    
    return 0;
}
