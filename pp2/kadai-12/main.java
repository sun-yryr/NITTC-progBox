import tsp.Algorithm;


class main {
    public static void main(String[] args) {
        Algorithm ag;
        try {
            ag = new Algorithm();
            for(int i=100; i<120; i++) {
                ag.genetic_algorithm(i);
            }
        } catch (Exception e) {
            System.out.print(e);
        }
        //System.out.printf("answer = %f\n", ans);
    }
}