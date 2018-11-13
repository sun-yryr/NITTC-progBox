import pr2calc.*;

class main {
    public static void main(String[] args) {
        double[][] test = {
            {4,3,2,1,4},
            {-2,4,-6,8,-34},
            {3,2,-3,-3,-4},
            {12,6,7,5,18.5}
        },
        kadai = {
            {2,1,3,4,2},
            {3,2,5,2,12},
            {3,4,1,-1,4},
            {-1,-3,1,3,-1}
        };
        SimultaneousEquation k = new SimultaneousEquation(kadai);
        k.solveByGaussWithCompleteSelection();
        k.printAnswer();
    }
}