#include <stdio.h>

#define DIM    64   /* ���o��������ʂ̎��� */

int main()
{
    FILE *fp1, *fp2 ;
    char fn[0x80] ;
    int data[20][DIM]; /* N�̓T���v�����CDim�͓����̎��� */
    int i=0,p=0,j=0,num=0;
    fp1 = fopen( "/Users/sun-mba/develop/school/ke/dic.txt","w") ;
    for( i = 0 ; i < 46 ; i++ ) {
        p=0,j=0;
        sprintf( fn, "/Users/sun-mba/develop/school/ke/ftr/%02d.ftr", i+1 );
        fp2 = fopen( fn,"r") ;
/* �t�@�C���̓��e��data[][]�ɓǂݍ��� */
        while(fscanf(fp2,"%d",&data[p][j])!=EOF){
            printf("%d,%d\n",p,j);
            j++;
            if(j==DIM){
                p++;
                j=0;
            }
        }
/* �e�����̕���ave[]�����߂�fp1�ɏ������� */
        for(p=0;p<DIM;p++){
            for(j=0;j<20;j++){
                num += data[j][p];
            }
            fprintf( fp1, "%lf\n", num/20.0 ) ;
            num=0;
        }
        fclose( fp2 ) ;
    }
    fclose( fp1 ) ;
    return 0;
}
