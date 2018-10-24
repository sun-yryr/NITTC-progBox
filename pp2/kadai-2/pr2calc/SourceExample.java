/* javaの基本的なコーディングを体験するクラス SourceExample */
package pr2calc;   // 現時点では「おまじない」

import java.io.*;

public class SourceExample{  

	private int a;
	private int[][] b;
	private String str;

    public SourceExample(){
        int h,i;

        this.a = -1;
        this.b = new int[2][2];
        for(h=0;h<this.b.length;h++){
            for(i=0;i<this.b[0].length;i++)
                this.b[h][i] = -1;
        }

        this.str = "";
    }

	public SourceExample(int a, int b[][], String str) {
        this.a = a;
        this.b = new int[3][3];
        for(int h=0;h<this.b.length;h++){
            for(int i=0;i<this.b[0].length;i++)
                this.b[h][i] = b[h][i];
        }
        this.str = str;
    }

        // ファイルからのデータ入力で変数を初期化するコンストラクタを作成
    public SourceExample(String fileName){
            try{
                    // ファイル"fileName"から、データを読み込むメソッドを呼び出す
                    if (this.loadData(fileName)) {
                        System.out.println("正しく読み込みました。");
                    } else {
                        System.out.println("データの形式が正しくありません。");
                    }
            }catch(IOException e){  System.out.println("ファイルからの入力に失敗しました。");}
    }

    /* 前回実装したインスタンスメソッド一式（表記は省略） */
    public void setA(int value){    //　メソッドを通して、フィールド変数の値を設定する（setterと呼ばれる）
        this.a = value;
    }

    public int getA(){	// メソッドを通して、フィールド変数の値を返す（getterと呼ばれる）
        return this.a;
    }

    public void setB(int[][] value){
        this.b = value;
    }

    public int[][] getB(){
        return this.b;
    }

    public void setStr(String value){
        this.str = value;
    }

    public String getStr(){
        return this.str;
    }

    public void showAllContentsOfB(){
        // 各自で必要な内容を記述すること
        for(int h=0;h<this.b.length;h++){
            for (int i=0; i<this.b[0].length; i++) {
                System.out.printf("%d", this.b[h][i]);
                if (i+1 != this.b[0].length) {
                    System.out.print(" , ");
                }
            }
            System.out.printf("\n");
        }
        System.out.println();
    }
    /* sampleより */
        
    private boolean loadData(String fileName) throws IOException{
		int h,i;
		int row, column;
		BufferedReader fin = new BufferedReader(new FileReader(fileName));
		String inputData;
		String[] inputValue;

        // inputData に、ファイルから文字列を一行分読み込む
        inputData = fin.readLine();
		// 得られた文字列データを、スペース(= "\\s") で区切り、配列 inputValue へ格納
        inputValue = inputData.split("\\s");

		if(inputValue.length != 1) {
            fin.close();
            return false;
        } else {
            // フィールド（インスタンス）変数 a に、inputValueの最初（0番目）の要素を代入
            this.a = Integer.parseInt(inputValue[0]);
            // もう一行読み込み、スペース区切りで inputValue へデータ(次に読み込む行列の行数＆列数）を格納
            inputData = fin.readLine();
            inputValue = inputData.split("\\s");
			if(inputValue.length != 2) {	// 行数＆列数の双方が格納されていなければ
                fin.close();
                return false;
            }
			else{
				// 変数 row に行数のデータ、column に列数のデータを代入
                row = Integer.parseInt(inputValue[0]);
                column = Integer.parseInt(inputValue[1]);
				this.b = new int[row][column];
                // 配列 b のh行i列目の要素に、読みんだファイルのh行目、(左から）i番目のデータを格納
                for (h=0; h<row; h++) {
                    inputValue = fin.readLine().split("\\s");
                    for (i=0; i<column; i++) {
                        this.b[h][i] = Integer.parseInt(inputValue[i]);
                    }
                }
                // 最後に一行読み込み、スペース区切りで inputValue へデータ(文字列）を格納
                inputData = fin.readLine();
                inputValue = inputData.split("\\s");
                // フィールド（インスタンス）変数 str に、格納した文字列を代入
                this.str = inputData;
			}
		}
		fin.close(); 
		return true;
    }
    
    public void saveData(String saveFileName) throws Exception {
        File save = new File(saveFileName);
        PrintWriter write = new PrintWriter(new BufferedWriter(new FileWriter(save)));
        write.println(this.a);
        write.printf("%d %d\n", this.b.length, this.b[0].length);
        for (int h=0; h<this.b.length; h++) {
            for (int i=0; i<this.b[0].length; i++) {
                write.print(this.b[h][i]);
                if (i+1 != this.b[0].length) {
                    write.print(" ");
                } else {
                    write.println();
                }
            }
        }
        write.print(this.str);
        write.close();
    }


    public static void main(String[] args) throws Exception {
    SourceExample    ex;    // SourceExample クラスのオブジェクト ex を宣言
            
            // 入力データの含まれているファイル名をsample.datとした場合
    //ex = new SourceExample("sample.dat");
    
    if(args.length != 1){
        System.out.println("引数が不適当です。データ入力用のファイル名を再度指定して下さい。");
        String fn = null;
        // キーボードからファイル名を入力して 変数 fn に代入する
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        fn = in.readLine();
        ex = new SourceExample(fn);
    }
    else
        ex = new SourceExample(args[0]);

    System.out.println("オブジェクトのaフィールドの値は"+ex.getA()+"です");
    System.out.println("");
    ex.showAllContentsOfB();
    System.out.println("");
    System.out.println(ex.getStr());
    ex.saveData("savedSample.dat");

    }

}