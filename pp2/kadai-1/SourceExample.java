//package pr2calc;

public class SourceExample{

    private int a;		// 青字の部分がフィールド変数（メソッドの外にある）。
    private int[][] b;	// クラス内の、main()メソッドを除く全メソッドで
    private String str;	// 利用可能


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

// フィールド変数 a, b, str　の値を内部で初期化（設定）するコンストラクタをもう一つ記述する

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

/* このプログラムを実行すると、以下の main メソッドに記述された動作が実行される */
    public static void main(String[] args){
        SourceExample    ex;    // SourceExample クラスのオブジェクト ex を宣言
        int value[][] = {{1,2,3},{4,5,6},{7,8,9}};

        //ex = new SourceExample();
        //ex.setA(10);
        // 上の二行をコメントアウトした上で、aを3、bを配列 value、str を文字列 "Hello World." として
        // 初期化するコンストラクタを用いて ex を生成せよ

        ex = new SourceExample(3, value, "Hello World.");

        System.out.println("オブジェクトのaフィールドの値は"+ex.getA()+"です\n");
        ex.showAllContentsOfB();
        System.out.println(ex.getStr());

    }
}