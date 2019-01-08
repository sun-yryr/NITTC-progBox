import java.math.*;
import pr2calc.*;
import java.util.function.*;

class main {
    public static void main(String[] args) {
        NonlinearEquation neq = new NonlinearEquation();
        DoubleFunction<Double> siki = (i) -> { return (Math.sin(i+3.0))/(i+3.0); };
        double ans = neq._solveNLEByBisectionMethod(siki);
        //System.out.printf("answer = %f\n", ans);
    }
}