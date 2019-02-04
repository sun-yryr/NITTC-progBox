import java.math.*;
import pr2calc.*;
import java.util.function.*;

class main {
    public static void main(String[] args) {
        NonlinearEquation neq = new NonlinearEquation();
        DoubleFunction<Double> siki = (i) -> (Math.exp(i) - i*3.05);
        double ans = neq._solveNLEByNewton(siki);
        //System.out.printf("answer = %f\n", ans);
    }
}