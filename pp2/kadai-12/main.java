import tsp.Algorithm;


class main {
    public static void main(String[] args) {
        Algorithm ag;
        try {
            ag = new Algorithm();
            ag.Display();
        } catch (Exception e) {
            System.out.print(e);
        }
        //System.out.printf("answer = %f\n", ans);
    }
}