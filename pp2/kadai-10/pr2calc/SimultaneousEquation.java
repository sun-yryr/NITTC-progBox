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

    protected void exchangeRows(int row1, int row2) {
        for (int i=0; i<super.getNumOfColumn(); i++) {
            double tmp = m[row1][i];
            m[row1][i] = m[row2][i];
            m[row2][i] = tmp;
        }
    }

    public void solveByGaussWithPartialSelection() {
        int i, j;
        //System.out.println("Start.");
        super.display();;
        System.out.println();
        for (j=0; j<super.getNumOfColumn()-1; j++) {
            i = j + 1;
            int maxrow = this.selectPivotFromRow(j);
            if (maxrow != -1) this.exchangeRows(j, maxrow);
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

    protected int selectPivotFromRow(int col) {
        if (col >= super.getNumOfRow()) return -1;
        double n = 0;
        int returnRow = col;
        for (int i=col; i<super.getNumOfRow(); i++) {
            if (n < Math.sqrt(Math.pow(m[i][col], 2))) {
                returnRow = i;
                n = Math.sqrt(Math.pow(m[i][col], 2));
            }
        }
        return returnRow;
    }

    protected int[] selectPivotAll(int col) {
        double n = 0;
        int[] returnData = new int[2];
        returnData[0] = col; returnData[1] = col;
        for (int i=col; i<super.getNumOfColumn()-1; i++) {
            for (int j=col; j<super.getNumOfRow(); j++) {
                if (n < m[j][i]) {
                    n = m[j][i];
                    returnData[0] = j; returnData[1] = i;
                }
            }
        }
        return returnData;
    }

    public void solveByGaussWithCompleteSelection() {
        int i, j;
        int[][] changed = new int[super.getNumOfColumn()-1][2];
        //System.out.println("Start.");
        super.display();;
        System.out.println();
        for (j=0; j<super.getNumOfColumn()-1; j++) {
            i = j + 1;
            int[] p = selectPivotAll(j);
            this.exchangeRowsAndColumns(j, j, p[0], p[1]);
            changed[j][0] = j; changed[j][1] = p[1];
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
        for (j=changed.length-1; 0<=j; j--) {
            double tmp = this.answers[changed[j][0]];
            this.answers[changed[j][0]] = this.answers[changed[j][1]];
            this.answers[changed[j][1]] = tmp;
        }
        //System.out.println("End.");
    }

    protected void exchangeRowsAndColumns(int row1, int col1, int row2, int col2) {
        this.exchangeRows(row1, row2);
        for (int i=0; i<super.getNumOfRow(); i++) {
            double tmp = m[i][col1];
            m[i][col1] = m[i][col2];
            m[i][col2] = tmp;
        }
    }
}