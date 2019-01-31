package tsp;

import java.io.*;
import java.util.Random;

public class Algorithm {
    private double[][] map;
    private int map_Rows,
                    map_Column;

    public Algorithm() throws Exception {
        try{
            map = new double[5000][5000];
            this.map_Rows = 5000;
            this.map_Column = 5000;
            FileReader filereader = new FileReader("./table.dat");
            BufferedReader bfreader = new BufferedReader(filereader);
            int row = 0;
            String str;
            while((str = bfreader.readLine()) != null) {
                String[] list = str.split(" ");
                for(int i=0; i<this.map_Rows; i++) {
                    this.map[row][i] = Double.parseDouble(list[i]);
                }
                row += 1;
            }
        }catch(FileNotFoundException e){
            System.out.println(e);
        }
    }

    public void Display() {
        for(int i=0; i<map_Rows; i++) {
            for(int j=0; j<map_Column; j++) {
                System.out.printf("%4f ", map[i][j]);
            }
            System.out.println();
        }
    }

    public char[] create_random(int start) {
        char[] a = new char[4999];
        for(int i=0; i<this.map_Rows-1; i++) {
            if(i == start) a[i] = this.map_Rows-1;
            else a[i] = i;
        }
        Random rnd = ThreadLocalRandom.current();
        for (int i = a.length - 1; i > 0; i--) {
            int index = rnd.nextInt(i + 1);
            // 要素入れ替え(swap)
            int tmp = a[index];
            a[index] = a[i];
            a[i] = tmp;
        }
        return a;
    }

    public void genetic_algorithm(int start) {
        ArrayList<Array<Char>> routes = new ArrayList<Array<Char>>();
        for(int i=0; i<5; i++) routes.add(create_random(start));

        
    }
}