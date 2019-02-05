import tsp.Algorithm;
import java.io.*;


class main {
    public static void main(String[] args) {
        Algorithm ag;
        try {
            ag = new Algorithm();
            System.out.print("始点を入力>> ");
            InputStreamReader isr = new InputStreamReader(System.in);
            BufferedReader br = new BufferedReader(isr);
            String buf = br.readLine();
            int x = Integer.parseInt(buf);
            ag.genetic_algorithm(x);
        } catch (Exception e) {
            System.out.print(e);
        }
        //System.out.printf("answer = %f\n", ans);
    }
}