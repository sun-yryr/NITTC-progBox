#include <stdio.h>
#include <math.h>

#define DIM    64    /* 抽出する特徴量の次元 */
#define CTGRY  46    /*文字数*/

double snow(int d[16],double dic[16]){
    return 1;
}

int main()
{
    FILE *fp;
    char fn[0x80];
    int f[DIM]={0};
    double data[DIM];
    double dist[CTGRY] = {0};
    double ave[CTGRY][DIM] = {0};
    int i=0,p=0,j=0,m=0;
    int num = 0;
    int all = 0;
    int total = 0;
    int count = 0;
    
    
    fp = fopen( "/Users/sun-mba/develop/school/ke/dic.txt","r");
    while(fscanf(fp,"%lf",&ave[i][j])!=EOF){
        if(j==DIM-1){
            j=0;
            i++;
        }
        else j++;
        
    }
    fclose( fp ) ;
    
    
    for(i=0;i<CTGRY;i++){
        sprintf( fn, "/Users/sun-mba/develop/school/ke/ftr/%02d.ftr", i+1 );
        fp = fopen( fn, "r" );
        num = 0 ;
        count = 0 ;
        while( 1 ) {
            /*
             *    一文字分の特徴をf[]に読み込む．
             *    読み込めなかった場合はbreak
             */
             for(j=0;j<DIM;j++){
                 if(fscanf(fp,"%d",&f[j])==EOF)break;
             }
             if(j!=DIM)break;

                    /* ここにそのプログラムを書いてください．*/

            num++ ;
            all++ ;

            /*
             *    字種ごとにユークリッド距離を計算する．
             */
            for( j = 0 ; j < CTGRY ; j++ ) {
                dist[j] = 0 ;
                m=0;
                for(p=0;p<DIM;p++){
                    m += pow((f[p]-ave[j][p]),2);
                }
                dist[j] = sqrt(m);
            }

                    /* f[0]～f[15]とave[i][0]～ave[i][15]が表す      */
                    /* ベクトルのユークリッド距離をもとめ，dist[i]に */
                    /* 代入するプログラムをここに書いてください．    */

            /*
             *    dist[]の中の最小値を求める．
             *    また，認識結果を出力する．
             */

                    /* dist[0]～dist[46]のうち，値が最少となるdist[k]を */
                    /* もとめるプログラムをここに書いてください．       */
             int min = 0;
             for(j=0;j<CTGRY;j++){
                 if(dist[min] > dist[j]) min = j;
             }
             

            /*
             *    認識精度を出すために正誤判定を行う．
             *    kはdist[]が最少となる番号
             */
            if( min == i ) {
                count++ ;
                total++ ;
            }
        }
        fclose( fp ) ;
        printf("%d[%d/%d]\n",i+1,count,num);
        /* num,countを用いて認識率を分数で出力する */
    }
    //トータルの認識率の出力
    printf("%d/%d\n",total,all);
    /* total, allを用いて認識率を分数で出力する */
        
        
    return 0;
}
