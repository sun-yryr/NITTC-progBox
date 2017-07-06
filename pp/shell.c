#include <stdio.h>
void sounyu(int[]);

int main()
{
    int i,j,h = 1,k;
    int moto[100] = {0};
    
    FILE *fp;
    fp = fopen("/Users/sun-mba/develop/pro-kadai/pro-kadai/data.txt","r"); //ファイル展開
    if(fp==NULL){
        printf("失敗¥n");
        return 0;
    }
    for (i=0; i<100; i++) {
        fscanf(fp,"%d",&moto[i]);
    }
    //ここまで普段の
    while(h<=100){
        h = 3*h + 1;
    }
    h /= 3;
    
    
    while(h>0){
        for (i=0; i<h; i++) {
            for (j=h+i; j<100; j += h) {
                int tmp = moto[j];
                for (k=j; k>=h && moto[k-h]>tmp; k-=h) {
                    moto[k] = moto[k-h];
                }
                moto[k] = tmp;
            }
        }
        h /= 3;
    }
    
    
    printf("\n表示します...\n");
    for(i=0;i<100;i++){
        printf("%3d ",moto[i]);
        //fprintf(fp2,"%d¥n",moto[i]);
        if ((i%10)==9) printf("\n");
    }
    return 0;
}

void sounyu(int moto[100]){
    int i,j,small;
    for(i=1;i<100;i++){
        small = moto[i];
        for(j=i;j>=1 && moto[j-1]>small;j--){
            moto[j] = moto[j-1];
        }
        moto[j] = small;
    }
}
