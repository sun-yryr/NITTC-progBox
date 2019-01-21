import java.math.*;
import pr2calc.*;
import java.util.function.*;

class main {
    public static void main(String[] args) {
        NonlinearEquation neq = new NonlinearEquation();
        DoubleFunction<Double> siki = (i) -> { 
            if(i == 0) return 1.0;
            else return (Math.sin(i+1.0))/(i+1.0);
        };
        double ans = neq._solveNLEByRegulaFalsi(siki);
        //System.out.printf("answer = %f\n", ans);
    }
}