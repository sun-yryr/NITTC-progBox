import pr2calc.*;

class main {
    public static void main(String[] args) {
        double[][] data = {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };
        SimultaneousEquation test = new SimultaneousEquation(data);
        test.normalize(0);
    }
}