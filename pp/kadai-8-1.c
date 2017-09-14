#include <stdio.h>
#define     N 1000000

int main()
{
    int i = 0;
    int moto;
    int data[N] = {0};
    FILE *fp;
    
    fp = fopen("/Users/sun-mba/develop/school/pp/kadai-8-1.txt","r"); //ファイル展開
    if(fp==NULL){
        printf("失敗¥n");
        return 0;
    }
    for (i=0; i<N; i++) {
        fscanf(fp,"%d",&data[i]);
    }
    
    printf("探査する整数を入力>>>\n");
    scanf("%d",&moto);
    
    int up = N-1;
    int down = 0;
    int a = 0;
    while (up!=down) {
        int a = ((up - down)/2)+ down;
        if(data[a]==moto){
            printf("[%d]番目です\n",a+1);
            return 0;
        }
        else if(data[a]>=moto)up = a - 1;//下にある
        else if(data[a]<=moto)down = a + 1;//上にある
    }
    printf("存在しない\n");
    return 0;
}
