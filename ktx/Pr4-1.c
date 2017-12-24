#include <stdio.h>

#define BUF_SIZE 32

int checksp(int c)
{
    /* 実装せよ 32と10*/
    if(c == 32 || c == 10 || c == 9)return 1;
    else return 0;
    
}

void compress(char *s)
{
    char *p = s;
    
    int count = 0;
    /* 行頭の空白を消去 */
    while(checksp(*p)){
        p++;
    }
    
    /* 新しい文字列を作成していく */
    while (*p != '\0' ) {
        while (checksp(*p)) {
            p++;
            count++;
        }
        if (count != 0) {
            if (*p == ',');
            else if (*p == '.') {
                *s = '.';
                s++;
                break;
            }
            else {
                *s = ' ';
                s++;
            }
            count = 0;
        }
        *s = *p;
        //printf("%c",*p);
        p++,s++;
    }
    *s = '\0';
}


int main(void)
{
    char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";
    s[sizeof(s) -1] = '\0';
    
    printf("Before = \"%s\"\n",s);
    compress(s);
    
    printf("After  = \"%s\"\n",s);
    
    return 0;
}
