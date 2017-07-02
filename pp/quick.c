#include <stdio.h>

void quick (int d[],int low,int max){
    if ((max-low) <= 1)return;
    int low2 = low;
    int max2 = max;
    int pivot = d[low];
    while (1) {
        low++;
        while (d[low] <= pivot) low++;
        max--;
        while (d[max] >= pivot) max--;
        if (low > max) break;
        
        int tmp = d[low];
        d[low] = d[max];
        d[max] = tmp;
    }
    int tmp = d[low2];
    d[low2] = d[max];
    d[max] = tmp;
    
    quick(d,low2,max);
    quick(d,low,max2);
    return;
}

int main (){
    int i,num=0;
    int check;
    int moto[10] = {0};
    int aho[10] = {0};
    
    FILE *fp;
    fp = fopen("/Users/sun-mba/develop/school/pp/data2.txt","r");
    if(fp==NULL){
        printf("error!:No file\n");
        return 0;
    }
    scanf("%d",&num);
    for(i=0;i<10;i++){
        fscanf(fp,"%d",&moto[i]);
        aho[i] = moto[i];
    }
    
    quick(moto,0,10);
    
    for(i=0;i<10;i++){
        printf("%10d ",moto[i]);
        printf("%10d\n",aho[i]);
    }
    return 0;
}
