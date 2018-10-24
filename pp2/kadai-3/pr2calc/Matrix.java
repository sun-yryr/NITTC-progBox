package pr2calc;

public class Matrix {
        // 必要なフィールド（インスタンス）変数を宣言せよ
    private double[][] m;
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


	public static void main(String[] args) {
/*
 * main メソッド中で今回作成した内積計算メソッドや行列同士、ベクトルと行列、
 * 行列とベクトルの積を計算するメソッドが正常に動いているかを確認せよ。
 */

// 行列・ベクトル定義、および演算処理の一例 （あくまで一例です）　課題の要求を満たすよう、各自で加筆・修正してください

		double[]
            x1 = { 2, -3,  7},
            y1 = {-1, -2,  2},

            k3_2 = {3, 7, -5, 2};
		double[][] 
			k2_1 = {
                { 1,  2,  3},
                { 3,  2, -1},
                { 4,  2,  6}
            },

			k2_2 = {
                { 5,  3,  1},
                { 3, -3,  2}
            },

			k3_1 = {
				{ 3},
                {-2}
            },

            k4_1 = {
                { 1,  2,  3},
                { 3,  2, -1},
                { 4,  2,  6}
            },

            k4_2 = {
                { 8,  2},
                {-3,  2},
                { 1,  6}
            },

            k5_1 = {
                { 2, -3},
                { 4,  2}
            },

            k5_2 = {
                {-5, -3,  1},
                {-3,  3,  2}
            };
                
                
        Matrix mat0 = new Matrix(x1),
            mat1 = new Matrix(k2_1),
            mat2 = new Matrix(k2_2),
            mat3 = new Matrix(k3_1),
            mat4 = new Matrix(k3_2),
            mat5 = new Matrix(k4_1),
            mat6 = new Matrix(k4_2),
            mat7 = new Matrix(k5_1),
            mat8 = new Matrix(k5_2);
// 以下は、行列・ベクトル演算の実行＆結果表示の一例．不要であれば削除し，課題の条件を満たす記述を新たに追加すること

        System.out.printf("(1) %.3f\n\n", mat0.getInnerProduct(y1));

		System.out.println("(2)");
		System.out.println("k2_1 = ");	mat1.display();
        System.out.println("k2_2 = ");	mat2.display();
        System.out.println("k2_1 * k2_2 =");
        if(mat1.multipliable(mat2) == true) {
            (mat1.multiplyMatrix(mat2)).display();    
        }
        System.out.println();

        System.out.println("(3)");
		System.out.println("k3_1 = ");	mat3.display();
        System.out.println("k3_2 = ");	mat4.display();
        System.out.println("k3_1 * k3_2 =");
        if(mat3.multipliable(mat4) == true) {
            (mat3.multiplyMatrix(mat4)).display();
        }
        System.out.println();

        System.out.println("(4)");
		System.out.println("k4_1 = ");	mat5.display();
        System.out.println("k4_2 = ");	mat6.display();
        System.out.println("k4_1 * k4_2 =");
        if(mat5.multipliable(mat6) == true) {
            (mat5.multiplyMatrix(mat6)).display(); 
        }
        System.out.println();

        System.out.println("(5)");
		System.out.println("k5_1 = ");	mat7.display();
        System.out.println("k5_2 = ");	mat8.display();
        System.out.println("k5_1 * k5_2 =");
        if(mat7.multipliable(mat8) == true) {
            (mat7.multiplyMatrix(mat8)).display();
        }
        System.out.println();
    }

}