package pr2calc;

public class Matrix {
        // 必要なフィールド（インスタンス）変数を宣言せよ
    protected double[][] m;
    private int numOfRow;
    private int numOfColumn;
	
	public Matrix(){
        // 行列の行数,列数を格納するインスタンス変数の値を0に初期化
        this.numOfRow = this.numOfColumn = 0;
        this.m = new double[2][2];
        for (int h=0; h<2; h++) {
            for (int i=0; i<2; i++) {
                this.m[h][i] = 0;
            }
        }
	}

	public Matrix(double[][] input){
        // 二次元配列 input の内容で、行列（インスタンス変数）を初期化せよ(例：配列 inputの0行0列目の値を、行列の0行0列目とする)
        this.numOfRow = input.length;
        this.numOfColumn = input[0].length;
        this.m = new double[numOfRow][numOfColumn];
        for (int h=0; h<numOfRow; h++) {
            for (int i=0; i<numOfColumn; i++) {
                this.m[h][i] = input[h][i];
            }
        }
    }

	public Matrix(double[] input){
        // 一次元配列 input の内容で、行列（インスタンス変数）を初期化せよ(例：行数は1、列数はinputの要素数とする)
        this.numOfRow = 1;
        this.numOfColumn = input.length;
        this.m = new double[numOfRow][numOfColumn];
        for (int i=0; i<numOfColumn; i++) {
            this.m[0][i] = input[i];
        }
	}

	public int getNumOfRow(){
		return this.numOfRow;
    }
        
	public int getNumOfColumn(){
		return this.numOfColumn;
    }

	public double showsComponentOf(int rowIndex, int columnIndex){
		// 指定した範囲が存在しない場合
                if(rowIndex < 0 || rowIndex >= numOfRow || columnIndex < 0 || columnIndex >= numOfColumn){
                        System.out.println("指定する要素は存在しません.");
                        System.exit(0);
                }
                // 指定された要素に対応する値を返す
                return this.m[rowIndex][columnIndex];
        }
        
	public void display(){
        // 行列内容の表示処理を実装せよ
        for (int h=0; h<numOfRow; h++) {
            System.out.print("[");
            for (int i=0; i<numOfColumn; i++) {
                System.out.printf("%.2f", this.m[h][i]);
                if (i+1 != numOfColumn) {
                    System.out.print(" , ");
                } else {
                    System.out.print("]\n");
                }
            }
        }
	}

	// ベクトルAとBの内積 A・Bの結果を返す
	public double getInnerProduct(double[][] input){
        double answer = 0;
        // Aが列ベクトルである場合、エラーメッセージを表示させて System.exit(0)
        if (this.m[0].length == 1) {
            System.out.println("このインスタンスは列ベクトルです。");
            System.exit(0);
        }
        // A, B 双方とも行ベクトル、かつ、要素数が等しければ内積を計算
        else if (this.m.length == 1 && input.length == 1 && this.m[0].length == input[0].length) {
            for (int i=0; i<this.numOfColumn; i++) {
                answer += this.m[0][i] * input[0][i];
            }
        } 
        // Aが行ベクトル、Bが列ベクトルで、要素数が等しければ内積を計算
        else if (this.m.length == 1 && input[0].length == 1 && this.m[0].length == input.length) {
            for (int i=0; i<this.numOfRow; i++) {
                answer += this.m[0][i] * input[i][0];
            }
        }
        // 内積計算が可能な条件を満たさない場合は、エラーメッセージを表示させてSystem.out.exit(0)
        else {
            System.out.println("計算できません。");
            System.exit(0);
        }
        // 計算結果を返す
        return answer;
    }
    public double getInnerProduct(double[] input) {
        double answer = 0;
        // Aが列ベクトルである場合、エラーメッセージを表示させて System.exit(0)
        if (this.m[0].length == 1) {
            System.out.println("このインスタンスは列ベクトルです。");
            System.exit(0);
        }
        // A, B 双方とも行ベクトル、かつ、要素数が等しければ内積を計算
        else if (this.m.length == 1 && this.m[0].length == input.length) {
            for (int i=0; i<this.numOfColumn; i++) {
                answer += this.m[0][i] * input[i];
            }
        } 
        // 内積計算が可能な条件を満たさない場合は、エラーメッセージを表示させてSystem.out.exit(0)
        else {
            System.out.println("計算できません。");
            System.exit(0);
        }
        // 計算結果を返す
        return answer;
    }

        // 行列同士、もしくは行列とベクトルとの積を計算する
    public Matrix multiplyMatrix(Matrix target){
        double[][] answer = new double[this.numOfRow][target.numOfColumn];
		// 掛けられる行列の列数と掛ける行列の行数が等しいなら
		if(this.numOfColumn == target.numOfRow){
            // 積の計算処理を実装せよ
            for (int h=0; h<this.numOfRow; h++) {
                for (int i=0; i<target.numOfColumn; i++) {
                    for (int tmp=0; tmp<this.numOfColumn; tmp++) {
                        answer[h][i] += this.m[h][tmp] * target.m[tmp][i];
                    }
                }
            }
            
        }
        else{
            System.out.println("要素数が計算できる組み合わせとなっていません");
            System.exit(0);
        }
                // 積の結果をMatrix型で返す
        return new Matrix(answer);
    }

    public boolean multipliable(Matrix y) {
        if (this.numOfColumn == y.numOfRow) return true;
        else {
            System.out.println("要素数が計算できる組み合わせとなっていません。");
            return false;
        }
    }

    public Matrix transpose() {
        double[][] returndata = new double[this.numOfColumn][this.numOfRow];
        for (int h=0; h<this.numOfColumn; h++) {
            for (int i=0; i<this.numOfRow; i++) {
                returndata[h][i] = this.m[i][h];
            }
        }
        return new Matrix(returndata);
    }

    public Matrix rotate(int theta) {
        double radious = convertIntoRadian(theta);
        Matrix newdata = new Matrix();
        if (this.numOfRow == 1 && this.numOfColumn == 2) {
            //行ベクトル
            double[][] tmp = {{this.m[0][0]}, {this.m[0][1]}};
            newdata = new Matrix(tmp);
        } else if (this.numOfColumn == 1 && this.numOfRow == 2) {
            //列ベクトル
            newdata = new Matrix(this.m);
        } else {
            System.out.println("このベクトルは回転できません。");
            System.exit(0);
        }
        double[][] sc = {
            {Math.cos(radious), -1.0*(Math.sin(radious))},
            {Math.sin(radious), Math.cos(radious)}
        };
        Matrix routa = new Matrix(sc);
        return routa.multiplyMatrix(newdata);
    }

    public static double convertIntoRadian(double theta) {
        if (theta < -360 || 360 < theta) {
            System.out.println("引数が不正です。");
            System.exit(0);
        }
        return (theta/180.0) * Math.PI;
    }
}