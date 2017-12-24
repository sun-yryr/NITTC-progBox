#include <stdio.h>
#include <math.h>

#define DIM    64    /* íäèoÇ∑ÇÈì¡í•ó ÇÃéüå≥ */
#define CTGRY  46    /*ï∂éöêî*/

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
             *    àÍï∂éöï™ÇÃì¡í•Çf[]Ç…ì«Ç›çûÇﬁÅD
             *    ì«Ç›çûÇﬂÇ»Ç©Ç¡ÇΩèÍçáÇÕbreak
             */
             for(j=0;j<DIM;j++){
                 if(fscanf(fp,"%d",&f[j])==EOF)break;
             }
             if(j!=DIM)break;

                    /* Ç±Ç±Ç…ÇªÇÃÉvÉçÉOÉâÉÄÇèëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅD*/

            num++ ;
            all++ ;

            /*
             *    éöéÌÇ≤Ç∆Ç…ÉÜÅ[ÉNÉäÉbÉhãóó£ÇåvéZÇ∑ÇÈÅD
             */
            for( j = 0 ; j < CTGRY ; j++ ) {
                dist[j] = 0 ;
                m=0;
                for(p=0;p<DIM;p++){
                    m += pow((f[p]-ave[j][p]),2);
                }
                dist[j] = sqrt(m);
            }

                    /* f[0]Å`f[15]Ç∆ave[i][0]Å`ave[i][15]Ç™ï\Ç∑      */
                    /* ÉxÉNÉgÉãÇÃÉÜÅ[ÉNÉäÉbÉhãóó£ÇÇ‡Ç∆ÇﬂÅCdist[i]Ç… */
                    /* ë„ì¸Ç∑ÇÈÉvÉçÉOÉâÉÄÇÇ±Ç±Ç…èëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅD    */

            /*
             *    dist[]ÇÃíÜÇÃç≈è¨ílÇãÅÇﬂÇÈÅD
             *    Ç‹ÇΩÅCîFéØåãâ ÇèoóÕÇ∑ÇÈÅD
             */

                    /* dist[0]Å`dist[46]ÇÃÇ§ÇøÅCílÇ™ç≈è≠Ç∆Ç»ÇÈdist[k]Ç */
                    /* Ç‡Ç∆ÇﬂÇÈÉvÉçÉOÉâÉÄÇÇ±Ç±Ç…èëÇ¢ÇƒÇ≠ÇæÇ≥Ç¢ÅD       */
             int min = 0;
             for(j=0;j<CTGRY;j++){
                 if(dist[min] > dist[j]) min = j;
             }
             

            /*
             *    îFéØê∏ìxÇèoÇ∑ÇΩÇﬂÇ…ê≥åÎîªíËÇçsÇ§ÅD
             *    kÇÕdist[]Ç™ç≈è≠Ç∆Ç»ÇÈî‘çÜ
             */
            if( min == i ) {
                count++ ;
                total++ ;
            }printf("%dを%dに認識\n",i+1,min+1);
        }
        fclose( fp ) ;
        printf("%d[%d/%d]\n",i+1,count,num);
        /* num,countÇópÇ¢ÇƒîFéØó¶Çï™êîÇ≈èoóÕÇ∑ÇÈ */
    }
    //ÉgÅ[É^ÉãÇÃîFéØó¶ÇÃèoóÕ
    printf("%d/%d\n",total,all);
    /* total, allÇópÇ¢ÇƒîFéØó¶Çï™êîÇ≈èoóÕÇ∑ÇÈ */
        
        
    return 0;
}
