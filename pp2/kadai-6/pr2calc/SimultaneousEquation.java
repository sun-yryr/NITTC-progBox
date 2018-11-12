package pr2calc;

import pr2calc.Matrix;

public class SimultaneousEquation extends Matrix {
    public double[] answers;

    public SimultaneousEquation(double[][] input){
        super(input);
        this.answers = new double[input.length];
        for (int i=0; i<this.answers.length; i++) {
            this.answers[i] = 0;
        }
    }
    
    public void normalize(int row){
        //System.out.println(m[row][1]);
        double tmp = m[row][row];
        for (int i=0; i<super.getNumOfColumn(); i++) {
            m[row][i] /= tmp;
        }
        //System.out.println("normalize complete.");
    }

    public void subtractRowFrom(int normalize_row, int target_row) {
        double tmp = m[target_row][normalize_row] / m[normalize_row][normalize_row];
        for (int i=0; i<super.getNumOfColumn(); i++) {
            m[target_row][i] -= m[normalize_row][i] * tmp;
        }
        //System.out.println("subtract complete.");
    }

    public void solveByGaussJordan() {
        int i, j;
        System.out.println("Start.");
        super.display();
        for (j=0; j<super.getNumOfColumn()-1; j++) {
            this.normalize(j);
            for (i=0; i<super.getNumOfRow(); i++) {
                if(i!=j) this.subtractRowFrom(j, i);
            }
            System.out.printf("%d行%d列目が1となるように割り、他の行の1列目が0となるように引く\n", j+1, j+1);
            super.display();
        }
        for (i=0; i<super.getNumOfRow(); i++) {
            this.answers[i] = m[i][super.getNumOfColumn()-1];
        }
        System.out.println("End.");
    }

    public void printAnswer() {
        int i;
        System.out.println("Answer:");
        for (i=0; i<this.answers.length; i++) {
            System.out.printf("x%d = %f", i+1, this.answers[i]);
            if(i!=this.answers.length-1) System.out.printf(", ");
            else System.out.println(".");
        }
    }

    public void solveByGauss() {
        int i, j;
        //System.out.println("Start.");
        super.display();;
        System.out.println();
        for (j=0; j<super.getNumOfColumn()-1; j++) {
            i = j + 1;
            while (i < super.getNumOfRow()) {
                this.subtractRowFrom(j, i);
                i++;
            }
            //System.out.printf("下の行の%d列目が0となるように引く\n", j+1);
            super.display();
            System.out.println();
        }
        for (j=this.answers.length-1; 0<=j; j--) {
            double tmp = 0;
            for (i=0; i<(super.getNumOfColumn()-1); i++) {
                tmp += m[j][i] * answers[i];
            }
            //System.out.printf("%f - %f / %f\n", m[j][super.getNumOfColumn()-1], tmp, m[j][j]);
            this.answers[j] = (m[j][super.getNumOfColumn()-1] - tmp) / m[j][j];
        }
        //System.out.println("End.");
    }
}