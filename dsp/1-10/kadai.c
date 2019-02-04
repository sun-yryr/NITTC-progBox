#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50

double gauss() {
    static double dispersion = 1, average = 0;
    double x1, x2, gauss;
    x1 = (double)rand()/(RAND_MAX);
    x2 = (double)rand()/(RAND_MAX);
    gauss = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2) * sqrt(dispersion) + average;
    return gauss;
}

double colored() {
    double color;
    static double old_color = 0;
    color = gauss() + 0.99 * old_color;
    old_color = color;
    return color;
}
double inner_product(double x[], double y[]) {
    double ans = 0;
    for(int i=0; i<N; i++) ans += x[i] * y[i];
    return ans
}

void lms_algo(double fillter[], double x[], double e[]) {
}

int main() {
    double wn[N], hn[N], xn[N];
    double d,y,e,xnorm;
    
    FILE *fp;
    if((fp = fopen("./w_imp50.txt", "r")) == NULL) {
        printf("load error\n");
    }
    for(int i=0; i<N; i++) 
        fscanf(fp, "%lf\n", wn[i]);

    fclose(fp);
    if((fp = fopen("./data.txt", "w")) == NULL) {
        printf("load error\n");
    }
    
    for(int j=0; j<N; j++) {
        for(int i=N-1; i>0; i--) xn[i]=xn[i-1];//入力ベクトルを生成
		xn[0]=gauss();
		//ファイルから読むものについては，1サンプルごとに読み込み

		//所望信号dの計算（firフィルタによるフィルタリング） d = xnとwnの内積
        d = inner_product(xn, wn);

		//フィルタからの出力信号yの計算（方法はdと同様）
        y = inner_product(xn, hn);

		//誤差信号eの計算
        e = d - y;

		//入力信号ベクトルxnのノルムの二乗||xn||^2の計算(xn同士の内積)
        xnorm = inner_product(xn, xn);
		//フィルタ係数のhnの計算
	    for(int m=0;m<N;i++) hn[m]+=step*xn[m]*e/(xnorm+0.000001);//フィルタ係数の更新

		//評価に使うデータ(eなど)をファイルへ1つずつ保存
    }
    return 0;
}