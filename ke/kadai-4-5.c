#include <stdio.h>
#include <math.h>

#define DIM    64    /* ���o��������ʂ̎��� */
#define CTGRY  46    /*������*/

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
             *    �ꕶ�����̓�����f[]�ɓǂݍ��ށD
             *    �ǂݍ��߂Ȃ������ꍇ��break
             */
             for(j=0;j<DIM;j++){
                 if(fscanf(fp,"%d",&f[j])==EOF)break;
             }
             if(j!=DIM)break;

                    /* �����ɂ��̃v���O�����������Ă��������D*/

            num++ ;
            all++ ;

            /*
             *    ���킲�ƂɃ��[�N���b�h�������v�Z����D
             */
            for( j = 0 ; j < CTGRY ; j++ ) {
                dist[j] = 0 ;
                m=0;
                for(p=0;p<DIM;p++){
                    m += pow((f[p]-ave[j][p]),2);
                }
                dist[j] = sqrt(m);
            }

                    /* f[0]�`f[15]��ave[i][0]�`ave[i][15]���\��      */
                    /* �x�N�g���̃��[�N���b�h���������Ƃ߁Cdist[i]�� */
                    /* �������v���O�����������ɏ����Ă��������D    */

            /*
             *    dist[]�̒��̍ŏ��l�����߂�D
             *    �܂��C�F�����ʂ��o�͂���D
             */

                    /* dist[0]�`dist[46]�̂����C�l���ŏ��ƂȂ�dist[k]�� */
                    /* ���Ƃ߂�v���O�����������ɏ����Ă��������D       */
             int min = 0;
             for(j=0;j<CTGRY;j++){
                 if(dist[min] > dist[j]) min = j;
             }
             

            /*
             *    �F�����x���o�����߂ɐ��딻����s���D
             *    k��dist[]���ŏ��ƂȂ�ԍ�
             */
            if( min == i ) {
                count++ ;
                total++ ;
            }
        }
        fclose( fp ) ;
        printf("%d[%d/%d]\n",i+1,count,num);
        /* num,count��p���ĔF�����𕪐��ŏo�͂��� */
    }
    //�g�[�^���̔F�����̏o��
    printf("%d/%d\n",total,all);
    /* total, all��p���ĔF�����𕪐��ŏo�͂��� */
        
        
    return 0;
}
