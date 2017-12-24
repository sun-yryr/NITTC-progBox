#include <stdio.h>
#include <math.h>

#define BUF_SIZE 32

int checkint(int c)
{
    for (int i = 48; i<=57; i++) {
        if (c == i)return 0;
    }
    if (c == 44) return 2;
    return 1;
}

int get_num2(int *a, int *b)
{
    char buf[BUF_SIZE+1];
    char ch_a[BUF_SIZE+1] = {0};
    char ch_b[BUF_SIZE+1] = {0};
    int i = 0,ck = 0,cou = 0,r = 0,index = 0;
    fgets(buf, BUF_SIZE, stdin);
    /*二つに分ける*/
    while (buf[i] != '\0') {
        //printf("buf[%d] = %d(%d)\n",i,buf[i],checkint(buf[i]));
        if (checkint(buf[i])==2) {
            ck = 1;cou = 0;i++;
        }
        if (ck == 0) { //前半
            ch_a[cou] = buf[i];
            cou++;
        }else if (ck == 1) { //後半
            ch_b[cou] = buf[i];
            cou++;
        }
        i++;
    }
    if (ck == 0) ch_a[i-1] = '\0'; //後半がない場合、なんで前半が1つぶんだけ多くなってしまうんだろうか......
    i = 0,ck = 0;
    while (ch_a[i] != '\0') { //前半のチェック
        ck += checkint(ch_a[i]);
        i++;
    }
    if (ck == 0 && i != 0) {　//後半の条件文は、前半が存在しない場合、ifに入ることを防ぐ
        r++;
        //printf("check\n");
        /*逆からint型に直して100x+10y+zの形にする*/
        for (index=0,*a=0; i>0; i--,index++) {
            *a += (ch_a[i-1] - '0') * pow(10,index);
        }
    } else i = 0;
    
    ck = 0;
    while (ch_b[i] != '\n') { //後半のチェック
        ck += checkint(ch_b[i]);
        i++;
    }
    if (ck == 0) {
        r++;
        //printf("check\n");
        /*逆からint型に直して100x+10y+zの形にする*/
        for (index=0,*b=0; i>0; i--,index++) {
            *b += (ch_b[i-1] - '0') * pow(10,index);
        }
    }
    return r;
}

int main(void)
{
    int a, b, r;
    
    printf(">");
    r = get_num2(&a,&b);
    
    printf("a = %d, b = %d, r = %d\n",a,b,r);
    
    return 0;
}
