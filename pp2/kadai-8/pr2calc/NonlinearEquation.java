package pr2calc;
import java.math.*;
import java.util.function.*;

public class NonlinearEquation{
        
        public static final double EPSILON = 0.001;
        public static final int MAXIMUM_IT = 100;
        
        private double initialValue_;
        private double answer_;
        private int iteration_;
        
        // コンストラクタ(最低一つ用意せよ）
        public NonlinearEquation(){
                initialValue_ = 1.0;
                iteration_ = 0;
        }
        public NonlinearEquation(double init) {
                initialValue_ = init;
                iteration_ = 0;
        }
        
        public double solveNLEByLinearIteration(DoubleFunction<Double> siki){
                double value = 0,      // x_k に対応
                       pastValue = 0;  // x_{k-1} に対応（初回のpastValue = x_0とする）
                do {
                        pastValue = value;
                        value = siki.apply(pastValue);
                        iteration_ += 1;
                        if (this.iteration_ == MAXIMUM_IT) {
                                System.out.println("最大指定回数に達しました。");
                                System.exit(-1);
                        }
                        System.out.printf("value = %f , pastvalue = %f\n", value, pastValue);
                }while(Math.abs(value - pastValue) >= EPSILON);
                // 初期反復解をvalueに設定し
                // |value - pastValue| が EPSILON 未満となる(近似解が見つかる)、もしくは
                // 繰り返し回数がMAXIMUM_IT 回に到達するまで繰り返し
                // 繰り返しで得られる反復解の途中経過を表示するようにすること
                //System.out.print(this.iteration_);
                System.out.printf("x = %f at iteration %d\n", value, this.iteration_);
                return value;
                
        }
}