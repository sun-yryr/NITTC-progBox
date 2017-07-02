

#include <stdio.h>

//関数プロトタイプ宣言
//使う
void print(char[64][64]);
void expand(char[],char[64][64]);
void outline(char[64][64]);
void smooth(char[64][64]);
void normalize(char[64][64],int);
void noise(char[64][64],int); //第二因数以下のノイズを削除する
void thinning(char[64][64]); //未実装

//使わない
void printimg(char[]);
void smooth2(char[64][64]);
int label(char[64][64]);
void labelP(char[64][64],int,int,int count);
int check(char[64][64],char[3][3],int,int);
void roll(char[3][3]);
void nuri(char[64][64],char[3][3],int,int,int rollCount);


int main() {
    char data[512];
    char pt[64][64] = {0};
    int i;
    
    FILE *fp;
    fp = fopen("/Users/sun-mba/develop/kadai/ke1/28.img", "rb");
    if(fp == NULL){
        printf("失敗\n");
        return 0;
    }
    for (i=0; i<2; i++) {
        fread(data, 512, 1, fp);
    }
    expand(data, pt);
    
    
    smooth(pt);
    normalize(pt,0);
    print(pt);
    printf("\n");
    thinning(pt);
    print(pt);
    
    return 0;
}

//ここから関数部分の定義
//imgファイルを[.][*]を使って表示する
void printimg(char data[512])
{
    int k,g,i;
    for(k=0;k<64;k++){
        for(g=0;g<8;g++){
            unsigned char b = 128;
            for(i=0;i<8;i++){
                if((data[8*k+g]&b)==0){
                    printf(".");
                }else{
                    printf("*");
                }
                b=b>>1;
            }
            
        }
        printf("\n");
    }
}

//二次元配列にした画像ファイルを表示（0,1）
void print(char pt[64][64]){
    int i,j;
    for (i=0; i<64; i++) {
        for (j=0; j<64; j++) {
            printf("%d",pt[i][j]);
        }
        printf("\n");
    }
}

//512bitデータを二次元配列に変換（0,1）
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

//枠線のみに画像処理
void outline(char pt[64][64]){
    int i,j;
    for (i=1; i<64; i++) {
        for (j=1; j<64; j++) {
            if (pt[i-1][j]!=0 && pt[i+1][j]!=0) { //上下左右が黒（1）で囲まれている
                if (pt[i][j-1]!=0 && pt[i][j+1]!=0) {
                    pt[i][j]=2;
                }}
        }
    }
    for (i=0; i<64; i++) { //2を0に全変換
        for (j=0; j<64; j++) {
            if (pt[i][j]==2){
                pt[i][j]=0;
            }
        }
    }
    
}

//スムージング処理（1ドット分のみ対応）
void smooth2(char pt[64][64]){
    int i,j;
    int x,y;
    int count = 0; //1ドット抜け判定に使う
    int iCheck[9],jCheck[9];
    for (int c=0; c<3 ; c++) { //とりあえず３回くらいやっとくかw
        for (i=1; i<63; i++) { //1バイト小さい箱でループ
            for (j=1; j<63; j++) {
                /*3*3での0判定開始*/
                count = 0;
                for (x=i-1; x<i+2; x++) {
                    for (y=j-1; y<j+2; y++) {
                        if(pt[x][y]==0){
                            iCheck[count] = x;
                            jCheck[count] = y; //0の座標をcountに格納
                            count++;
                        }
                    }
                }/*3*3での0判定終了*/
                
                if (count==1) {      //１ドットズレを修正（強制的に上下左右中央を１で上書き）
                    pt[i-1][j] = 1;
                    pt[i][j-1] = 1;
                    pt[i][j+1] = 1;
                    pt[i+1][j] = 1;
                    pt[i][j] = 1;
                }else if (count==2){ //1ドット抜けを修正（端抜けの場合に中央を０で上書き）
                    if (iCheck[0]!=i && jCheck[0]!=j) { //中央ではない
                        if (iCheck[0]==iCheck[1]) {
                            if (jCheck[1] - jCheck[0] == 2) {
                                pt[iCheck[0]][j] = 0;
                            }
                        }else if (jCheck[0]==jCheck[1]){
                            if (iCheck[1] - iCheck[0] == 2) {
                                pt[i][jCheck[0]] = 0;
                            }
                        }
                    }
                }/*追加のスムージングを書くならここにelse if*/
            }
        }
    }
}

//スムージング処理（3*3のレイヤーをかけるタイプ）
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

//正規化（拡大）sineが1なら縦横比維持
void normalize(char pt[64][64], int sine){
    int i,j,i1,j1;
    int x,y;
    int iSta=0,iEnd=0,jSta=0,jEnd=0;
    char after[64][64] = {0};
    for (i=0,i1=63; i<64; i++,i1--) {
        for (j=0,j1=63; j<64; j++,j1--) {
            if (pt[i][j]==1 && iSta==0) {
                iSta = i;
                jSta = j;
            }else if (pt[i][j]==1 && jSta>j) {
                jSta = j;
            }
            if (pt[i1][j1]==1 && iEnd==0) {
                iEnd = i1;
                jEnd = j1;
            }else if (pt[i1][j1]==1 && jEnd<j1){
                jEnd = j1;
            }
            
        }
    }
    double length = jEnd - jSta; //横の長さ
    double high = iEnd - iSta;   //縦の長さ
    double longer = 0.0;         //長い方を保存する
    
    if (sine == 1) {
        if (length < high) {
            longer = high;
        }
        else longer = length;
    }
    
    for (i=0; i<64; i++) {
        for (j=0; j<64; j++) {
            if (sine==1) {
                x = (int)( i * ( longer / 64.0 ) +  iSta + 0.5);
                y = (int)( j * ( longer / 64.0 ) +  jSta + 0.5);
            }else {
                x = (int)( i * ( high / 64.0 ) +  iSta + 0.5);
                y = (int)( j * ( length / 64.0 ) +  jSta + 0.5);
            }
            if (x>=64 || y>=64) break;
            after[i][j] = pt[x][y];
        }
    }
    if (sine == 1) { //中央揃えにする
        iEnd = 0,jEnd = 0;
        for (i=63; i>=0; i--) {
            for (j=63; j>=0; j--) {
                if (after[i][j]==1 && iEnd==0) {
                    iEnd = i;
                    jEnd = j;
                }else if (after[i][j]==1 && jEnd<j){
                    jEnd = j;
                }
            }
        }
        iEnd = ( 63 - iEnd ) / 2;
        jEnd = ( 63 - jEnd ) / 2;
    }else {
        jEnd = 0;
        iEnd = 0;
    }
    
    for (i=0; i<64-iEnd; i++) {
        for (j=0; j<64-jEnd; j++) {
            pt[i+iEnd][j+jEnd] = after[i][j];
        }
    }
}

//ラベル付け
int label(char pt[64][64]){
    int i,j;
    int count = 1;
    for (i=0; i<64; i++) {
        for (j=0; j<64; j++) {
            if (pt[i][j]==1) {
                count++;
                labelP(pt,i,j,count);
            }
        }
    }
    if (count>=255) count = 0;
    return count;
}

void labelP(char pt[64][64],int i,int j,int count){
    pt[i][j] = count;
    if (i==-1 || j==-1 || i==64 || j == 64)return;
    if(pt[i-1][j-1]==1) labelP(pt, i-1, j-1, count);
    if(pt[i-1][j  ]==1) labelP(pt, i-1, j  , count);
    if(pt[i-1][j+1]==1) labelP(pt, i-1, j+1, count);
    
    if(pt[i  ][j-1]==1) labelP(pt, i, j-1, count);
    if(pt[i  ][j+1]==1) labelP(pt, i, j+1, count);
    
    if(pt[i+1][j-1]==1) labelP(pt, i+1, j-1, count);
    if(pt[i+1][j  ]==1) labelP(pt, i+1, j  , count);
    if(pt[i+1][j+1]==1) labelP(pt, i+1, j+1, count);
    
    return;
}

//ノイズ除去
void noise(char pt[64][64], int num){
    int noise = label(pt);
    int count = 0;
    while (noise>1) {
        for (int i=0; i<64; i++) {
            for (int j=0; j<64; j++) {
                if (pt[i][j]==noise) {
                    count++;
                }
            }
        }
        if (count<num) {
            for (int i=0; i<64; i++) {
                for (int j=0; j<64; j++) {
                    if (pt[i][j]==noise) pt[i][j] = 0;
                }
            }
        }
        count = 0;
        noise--;
    }
    for (int i=0; i<64; i++) { //0以外を1に全変換
        for (int j=0; j<64; j++) {
            if (pt[i][j]!=0)pt[i][j]=1;
        }
    }
}

//細線化（未実装）
void thinning(char pt[64][64]){
    int i,j;
    int count;
    int hs = 4;
    while (hs!=1){
    for (i=1; i<64; i++) {
        for (j=1; j<64; j++) {
            if (pt[i-1][j]!=0 && pt[i+1][j]!=0) { //上下左右が黒（1）で囲まれている
                if (pt[i][j-1]!=0 && pt[i][j+1]!=0) {
                    pt[i][j]=2;
                }else{
                    pt[i][j]=2;
                }
            }else{
                pt[i][j]=2;
            }
        }
    }
    for (i=0; i<64; i++) { //1を0,2を1に全変換
        for (j=0; j<64; j++) {
            if (pt[i][j]==2){
                pt[i][j]=1;
            }else if(pt[i][j]==1){
                pt[i][j]=0;
            }
        }
    }
        hs--;
    }
    
    
    
    
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
