#include <stdio.h>

#define DIM    64    /* 抽出する特徴量の次元 */

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
		
		/*カウント用*/
		for(i=0;i<64;i++){
			for(j=0;j<64;j++){
				if(p[j][i]==label) count++;		
			}
		}
	
			/*削除*/
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

	/*ラベリング，ノイズ除去 
	成功で0を返し，255以上のラベルで処理を中止*/
	
int label(char p[64][64]){
	
	int i,j;
	int count=1;//代入用
	

	
	/*黒なら再帰用の関数を呼ぶ*/
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]==1){
				count++;
				p[j][i]=count;
				label_sub(count,p,j,i);
			}
			if(count-1>=255) return 1; //失敗
		}
	}
	

	
	int size = 4;
	
	
	noise(p,size); //size以下削除
	
	
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]!=0) p[j][i]=1;
			
		}
	}
	
	return 0;
}



//90度回転させる関数
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

/*3*3配列の等号判定
 0度で1、90度で2、180度で3、270度で4を返す。どれにも当てはまらなかったら-1 */
int check(char pt[64][64],char ray[3][3],int i,int j){
    int x,y;
    int count = 0;
    int ext = -1;
    char box[3][3] = {0};
    i--,j--;
    for (x=0; x<3; x++,i++) { //コピー
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

//塗る
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
    //変数記述
    int i,j,c;
    
    
    //レイヤー
    char bit1[3][3] = {{0,1,0},{1,1,1},{1,1,1}};
    char fix1[3][3] = {{0,0,0},{1,1,1},{1,1,1}};
    
    char bit2[3][3] = {{1,0,1},{1,1,1},{1,1,1}};
    char fix2[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //処理開始
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
 *    特徴量抽出のための関数extract()を定義する．
 *    pで与えられた画像から，DIM個の数値を特徴として
 *    抽出し，fに書き込む関数．
 */
void extract( char p[64][64], int f[DIM] )
{
    int i,j;
    int fcount = 0;
    int count = 0;
    for(i=0;i<DIM;i++)f[i]=0;//f初期化
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
     *    以下，データファイルごとに特徴抽出を行う
     */
    for( i = 0 ; i < 46 ; i++ ) {
        /*
         *    画像ファイル・特徴ファイルの名前を設定する
         */
        sprintf( infn, "/Users/sun-mba/develop/school/ke/expdat/c%02d.img", i+1 ) ;
        sprintf( outfn, "/Users/sun-mba/develop/school/ke/ftr/%02d.ftr", i+1 ) ;

        /*
         *    文字画像ファイルおよび特徴ファイルを開く
         */
        fp1 = fopen( infn, "rb" ) ;
        fp2 = fopen( outfn, "w" ) ;

        /*
         *    ファイル内に文字画像データがある限り
         *    下記の処理を繰り返す
         */
        while( fread( img, 512, 1,fp1 ) == 1 ) {
            /*
             *    前処理
             */
            expand( img, p ) ;
            label( p ) ;
            smooth( p ) ;    /* 発展課題なので作った人のみ */
            normalize( p ) ;
            outline( p ) ;
            /*
             *    特徴抽出．ここではDIM個の数値を抽出する．
             */
            extract( p, f ) ;
            /*
             *    特徴出力
             */
            for( j = 0 ; j < DIM ; j++ ) {
                fprintf( fp2, "%d\n", f[j] ) ;
            }
        }

        /*
         *    ファイルのクローズ
         */
        fclose( fp1 ) ;
        fclose( fp2 ) ;
        
    }
}


