#include <stdio.h>

#define DIM    64    /* ���o��������ʂ̎��� */

void expand(char data[512],char pattern [64][64])
{
    int k,g,i;
    for(k=0;k<64;k++){
        for(g=0;g<8;g++){
            unsigned char b = 128;
            for(i=0;i<8;i++){
                if((data[8*k+g]&b)==0){
                    pattern[k][8*g+i]=0;
                }else{
                    pattern[k][8*g+i]=1;
                }
                b=b>>1;
            }
            
        }
    }
}

void outline( char p[64][64] ){
	int i,j;
	for(i=1;i<63;i++){
		for(j=1;j<63;j++){
			if(p[i][j]==0)continue;
			if(p[i-1][j]>=1&&p[i][j-1]>=1&&p[i][j+1]>=1&&p[i+1][j]>=1){
				p[i][j]=2;
			}
		}
	}
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[i][j]!=1){
				p[i][j]=0;
			}
		}
	}
}

void normalize(char pt[64][64]) {
	char bigger[64][64];
	int x,y;
	double w=0,h=0;
	int x0=64,y0=64;
	int bgx,bgy;
	for(y=0;y<64;y++) {
		for(x=0;x<64;x++) {
			if(pt[y][x]==1) {
				if(x0>x)x0=x;
				if(y0>y)y0=y;
				if(w<x)w=x;
				if(h<y)h=y;
			}
		}
	}
	w=w-x0;
	h=h-y0;
	
	for(y=0;y<64;y++) {
		for(x=0;x<64;x++) {
			bgx=(int)(x*(w/64) + x0 + 0.5);
			bgy=(int)(y*(h/64) + y0 + 0.5);
			bigger[y][x]=pt[bgy][bgx];
		}
	}
	for(y=0;y<64;y++) {
		for(x=0;x<64;x++) {
			pt[y][x]=bigger[y][x];
		}
	}
}

void noise( char p[64][64], int size ){

	int label=1;
	int count=0;
	int i,j;

	while(label!=255){
		
		label++;
		
		/*�J�E���g�p*/
		for(i=0;i<64;i++){
			for(j=0;j<64;j++){
				if(p[j][i]==label) count++;		
			}
		}
	
			/*�폜*/
		if(count<=size){
			for(i=0;i<64;i++){
				for(j=0;j<64;j++){
					if(p[j][i]==label) p[j][i]=0;
				}
			}
		}
		
		
	}
}


void label_sub(int count_sub, char p[64][64],int j,int i){

	
	if((j-1)>=0 && (i-1)>=0 && p[j-1][i-1]==1){
		p[j-1][i-1]=count_sub;
		label_sub(count_sub, p,j-1,i-1);
	}
	if((j-1)>=0 && p[j-1][i+1]==1){
		p[j-1][i+1]=count_sub;
		label_sub(count_sub, p,j-1,i+1);
	}
	if((i-1)>=0 && p[j+1][i-1]==1){
		p[j+1][i-1]=count_sub;
		label_sub(count_sub, p,j+1,i-1);
	}
	if(p[j+1][i+1]==1){
		p[j+1][i+1]=count_sub;
		label_sub(count_sub, p,j+1,i+1);
	}
	
	return;

}

	/*���x�����O�C�m�C�Y���� 
	������0��Ԃ��C255�ȏ�̃��x���ŏ����𒆎~*/
	
int label(char p[64][64]){
	
	int i,j;
	int count=1;//����p
	

	
	/*���Ȃ�ċA�p�̊֐����Ă�*/
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]==1){
				count++;
				p[j][i]=count;
				label_sub(count,p,j,i);
			}
			if(count-1>=255) return 1; //���s
		}
	}
	

	
	int size = 4;
	
	
	noise(p,size); //size�ȉ��폜
	
	
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]!=0) p[j][i]=1;
			
		}
	}
	
	return 0;
}



//90�x��]������֐�
void roll(char ray[3][3]){
    int a = 0;
    a = ray[0][0];
    ray[0][0] = ray[2][0];
    ray[2][0] = a;
    
    a = ray[2][0];
    ray[2][0] = ray[2][2];
    ray[2][2] = a;
    
    a = ray[2][2];
    ray[2][2] = ray[0][2];
    ray[0][2] = a;
    
    a = ray[0][1];
    ray[0][1] = ray[1][0];
    ray[1][0] = a;
    
    a = ray[1][0];
    ray[1][0] = ray[2][1];
    ray[2][1] = a;
    
    a = ray[2][1];
    ray[2][1] = ray[1][2];
    ray[1][2] = a;
}

/*3*3�z��̓�������
 0�x��1�A90�x��2�A180�x��3�A270�x��4��Ԃ��B�ǂ�ɂ����Ă͂܂�Ȃ�������-1 */
int check(char pt[64][64],char ray[3][3],int i,int j){
    int x,y;
    int count = 0;
    int ext = -1;
    char box[3][3] = {0};
    i--,j--;
    for (x=0; x<3; x++,i++) { //�R�s�[
        for (y=0; y<3; y++,j++) {
            box[x][y] = pt[i][j];
        }
        j = j - 3;
    }
    
    for (x=0; x<3; x++) {
        for (y=0; y<3; y++) {
            if (box[x][y]==ray[x][y]) count++;
        }
    }
    if (count==9) ext = 1;
    count = 0;
    roll(ray);
    
    for (x=0; x<3; x++) {
        for (y=0; y<3; y++) {
            if (box[x][y]==ray[x][y]) count++;
        }
    }
    if (count==9) ext = 2;
    count = 0;
    roll(ray);
    
    for (x=0; x<3; x++) {
        for (y=0; y<3; y++) {
            if (box[x][y]==ray[x][y]) count++;
        }
    }
    if (count==9) ext = 3;
    count = 0;
    roll(ray);
    
    for (x=0; x<3; x++) {
        for (y=0; y<3; y++) {
            if (box[x][y]==ray[x][y]) count++;
        }
    }
    if (count==9) ext = 4;
    count = 0;
    roll(ray);
    
    return ext;
}

//�h��
void nuri(char pt[64][64],char ray[3][3],int i,int j,int rollCount){
    int x,y;
    int count = 1;
    while (count!=rollCount) {
        roll(ray);
        count++;
    }
    
    i--,j--;
    for (x=0; x<3; x++,i++,j-=3) {
        for (y=0; y<3; y++,j++) {
            pt[i][j] = ray[x][y];
        }
    }
    count = 5 - rollCount;
    while (count!=0) {
        roll(ray);
        count--;
    }
}

void smooth(char pt[64][64]){
    //�ϐ��L�q
    int i,j,c;
    
    
    //���C���[
    char bit1[3][3] = {{0,1,0},{1,1,1},{1,1,1}};
    char fix1[3][3] = {{0,0,0},{1,1,1},{1,1,1}};
    
    char bit2[3][3] = {{1,0,1},{1,1,1},{1,1,1}};
    char fix2[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //�����J�n
    for (i=1; i<63; i++) {
        for (j=1; j<63; j++) {
            c = check(pt, bit1, i, j);
            if(c!=-1) nuri(pt, fix1, i, j, c);
            c = check(pt, bit2, i, j);
            if(c!=-1) nuri(pt, fix2, i, j, c);
        }
    }
}
/*
 *    �����ʒ��o�̂��߂̊֐�extract()���`����D
 *    p�ŗ^����ꂽ�摜����CDIM�̐��l������Ƃ���
 *    ���o���Cf�ɏ������ފ֐��D
 */
void extract( char p[64][64], int f[DIM] )
{
    int i,j;
    int fcount = 0;
    int count = 0;
    for(i=0;i<DIM;i++)f[i]=0;//f������
    int s;
    int r;
    for(s=0;s<64;s+=8){
        for(r=0;r<64;r+=8){
            count = 0;
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if(p[i+s][j+r] == 1)count++;
                }
            }
            f[fcount] = count;
            fcount++;
        }
    }
    return;
}


int main( )
{
    FILE    *fp1, *fp2 ;
    char    infn[0x80], outfn[0x80] ;
    char    img[512] ;
    char    p[64][64] ;
    int     f[DIM] ;
    int     num, i=0, j=0 ;

    /*
     *    �ȉ��C�f�[�^�t�@�C�����Ƃɓ������o���s��
     */
    for( i = 0 ; i < 46 ; i++ ) {
        /*
         *    �摜�t�@�C���E�����t�@�C���̖��O��ݒ肷��
         */
        sprintf( infn, "/Users/sun-mba/develop/school/ke/expdat/c%02d.img", i+1 ) ;
        sprintf( outfn, "/Users/sun-mba/develop/school/ke/ftr/%02d.ftr", i+1 ) ;

        /*
         *    �����摜�t�@�C������ѓ����t�@�C�����J��
         */
        fp1 = fopen( infn, "rb" ) ;
        fp2 = fopen( outfn, "w" ) ;

        /*
         *    �t�@�C�����ɕ����摜�f�[�^���������
         *    ���L�̏������J��Ԃ�
         */
        while( fread( img, 512, 1,fp1 ) == 1 ) {
            /*
             *    �O����
             */
            expand( img, p ) ;
            label( p ) ;
            smooth( p ) ;    /* ���W�ۑ�Ȃ̂ō�����l�̂� */
            normalize( p ) ;
            outline( p ) ;
            /*
             *    �������o�D�����ł�DIM�̐��l�𒊏o����D
             */
            extract( p, f ) ;
            /*
             *    �����o��
             */
            for( j = 0 ; j < DIM ; j++ ) {
                fprintf( fp2, "%d\n", f[j] ) ;
            }
        }

        /*
         *    �t�@�C���̃N���[�Y
         */
        fclose( fp1 ) ;
        fclose( fp2 ) ;
        
    }
}


