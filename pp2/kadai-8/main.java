import java.math.*;
import pr2calc.*;
import java.util.function.*;

class main {
    public static void main(String[] args) {
        NonlinearEquation neq = new NonlinearEquation(4.0);
        DoubleFunction<Double> siki = (i) -> { return Math.sqrt(18 + i); };
        double ans = neq.solveNLEByLinearIteration(siki);
        //System.out.printf("answer = %f\n", ans);
    }
}