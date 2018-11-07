package pr2calc;

import pr2calc.Matrix;

public class SimultaneousEquation extends Matrix {
    private double[] answers;

    public SimultaneousEquation(double[][] input){
        super(input);
        this.answers = new double[input.length];
    }
    
    public void normalize(int row){
        //System.out.println(m[row][1]);
        double tmp = m[row][0];
        for (int i=0; i<super.getNumOfColumn(); i++) {
            m[row][i] /= tmp;
            System.out.println(m[row][i]);
        }
    }
}