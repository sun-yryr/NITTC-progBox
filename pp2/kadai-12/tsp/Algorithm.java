package tsp;

import java.io.*;
import java.util.Random;

public class Algorithm {
    private int[][] map;
    private int map_Rows,
                    map_Column;

    public Algorithm() throws Exception {
        try{
            map = new int[5000][5000];
            this.map_Rows = 5000;
            this.map_Column = 5000;
            FileReader filereader = new FileReader("./table.dat");
            BufferedReader bfreader = new BufferedReader(filereader);
            int row = 0;
            String str;
            while((str = bfreader.readLine()) != null) {
                String[] list = str.split(" ");
                for(int i=0; i<this.map_Rows; i++) {
                    this.map[row][i] = Integer.parseInt(list[i]);
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
                System.out.printf("%4d ", map[i][j]);
            }
            System.out.println();
        }
    }

    public void genetic_algorithm(int start) {
        int route[] = new int[5000];
        boolean visited[] = new boolean[5000];
        route[0] = start;
        visited[start] = true;
        for(int i=1; i<5000; i++) {
            int index = 0;
            int min = 1000000000;
            for(int j=0; j<5000; j++) {
                if(i == j);
                else if(map[route[i-1]][j] < min && visited[j] == false) {
                    min = map[route[i-1]][j];
                    index = j;
                }
            }
            visited[index] = true;
            route[i] = index;
        }
        int ans = 0;
        for(int i=1; i<5000; i++) {
            ans += map[route[i-1]][route[i]];
        }
        System.out.println(ans);
    }
}