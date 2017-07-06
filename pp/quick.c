/*1千万のソートはできましたが、100万のソートだと"Segmentation fault: 11"
 のエラーで止まってしまいます。quickソート"999991,9999999"でエラーです*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 //100文字読み取り

void quick (int d[],int low,int max){
    if ((max-low) <= 0)return;
    int low2 = low;
    int max2 = max;
    int pivot = d[low];
    while (1) {
        low++;
        while (d[low] < pivot) low++;
        while (d[max] > pivot) max--;
        if (low >= max) break;
        
        int tmp = d[low];
        d[low] = d[max];
        d[max] = tmp;
    }
    int tmp = d[low2];
    d[low2] = d[max];
    d[max] = tmp;
    //printf("%d,%d\n",low2,max-1);
    quick(d,low2,max-1);
    //printf("%d,%d\n",low,max2);
    quick(d,low,max2);
    return;
}

int main (){
    int i=0,j=0,num=0;
    int check;
    char aho[SIZE];
    int *moto;
    
    FILE *fp;
    fp = fopen("/Users/sun-mba/develop/school/pp/sample2.txt","r");
    if(fp==NULL){
        printf("error!:No file\n");
        return 0;
    }
    while(fgets(aho,SIZE,fp)!= NULL)i++;
    moto = (int *)malloc(sizeof(int)*i);
    if (moto==NULL) {
        printf("** out of memory **\n");
        exit(1);
    }
    printf("%d\n",i);
    rewind(fp);
    while(fscanf(fp,"%d",&moto[j])!= EOF)j++;
    quick(moto,0,i-1);
    for(j=0;j<i;j++){
        printf("[%d]%d  ",j,moto[j]);
        if(j%10==9)printf("\n");
    }
    return 0;
}
