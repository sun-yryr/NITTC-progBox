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

        public double _solveNLEByBisectionMethod(DoubleFunction<Double> siki) {
                double NEGATIVE_MAX = 0.0,
                        POSITIVE_MAX = 3.0,
                        xPastMid = 0.0,
                        midX = 0.0,
                        fmidX = 0.0;
                do {
                        this.iteration_ += 1;
                        if (this.iteration_ == MAXIMUM_IT) {
                                System.out.println("最大指定回数に達しました。");
                                System.exit(-1);
                        }
                        xPastMid = midX;
                        midX = (POSITIVE_MAX + NEGATIVE_MAX)/2.0;
                        fmidX = siki.apply(midX);
                        if(midX == 0) fmidX = 1.0;
                        if (fmidX > 0) {
                                NEGATIVE_MAX = midX;
                        } else if (fmidX < 0) {
                                POSITIVE_MAX = midX;
                        }
                        System.out.printf("xMid = %.9f, f(xMid) = %.9f, xPastMid = %.9f\n", midX, fmidX, xPastMid);
                }while(Math.abs(midX - xPastMid) >= this.EPSILON);
                System.out.printf("x = %f at iteration %d\n", midX, this.iteration_);
                return midX;
        }

        public double _solveNLEByRegulaFalsi(DoubleFunction<Double> siki) {
                double NEGATIVE_MAX = 0.0,
                        POSITIVE_MAX = 5.0,
                        xPastNext = 0.0,
                        xNext = 0.0;
                do {
                        this.iteration_ += 1;
                        if (this.iteration_ == MAXIMUM_IT) {
                                System.out.println("最大指定回数に達しました。");
                                System.exit(-1);
                        }
                        xPastNext = xNext;
                        xNext = (NEGATIVE_MAX*siki.apply(POSITIVE_MAX) - POSITIVE_MAX*siki.apply(NEGATIVE_MAX)) / (siki.apply(POSITIVE_MAX) - siki.apply(NEGATIVE_MAX));
                        this.answer_ = siki.apply(xNext);
                        if(this.answer_ > 0) {
                                NEGATIVE_MAX = xNext;
                        } else if(this.answer_ < 0) {
                                POSITIVE_MAX = xNext;
                        }
                        System.out.printf("xNext = %f, f(xNext)=%f, xPastNext = %f\n", xNext, this.answer_, xPastNext);
                }while(Math.abs(xNext - xPastNext) >= this.EPSILON);
                System.out.printf("x = %f at iteration %d.\n", xNext, this.iteration_);
                return xNext;
        }

        public double _solveNLEByNewton(DoubleFunction<Double> siki) {
                double  xPastNext = 1.19,
                        xNext = 0.0,
                        tmp = 0.0,
                        a = 3.05;
                do {
                        if (this.iteration_ != 0) xPastNext = xNext;
                        this.iteration_ += 1;
                        if (this.iteration_ == MAXIMUM_IT) {
                                System.out.println("最大指定回数に達しました。");
                                System.exit(-1);
                        }
                        tmp = Math.exp(xPastNext) - a;
                        xNext = xPastNext - (siki.apply(xPastNext)/tmp);
                        System.out.printf("xNext = %f, f(xNext)=%f\n", xNext, siki.apply(xNext));
                } while (Math.abs(xNext - xPastNext) >= this.EPSILON);
                System.out.printf("x = %f at iteration %d.\n", xNext, this.iteration_);
                return xNext;
        }
}