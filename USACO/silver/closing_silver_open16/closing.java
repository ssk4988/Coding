/*
ID: ssk49881
LANG: JAVA
TASK: closing
*/

import java.io.*;
import java.util.*;

public class closing {
    public static int numComponents = 0;
    public static int numBarns;
    public static Barn[] barns;
    public static boolean[][] adjacent;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("10.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new
        // FileWriter("closing.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numBarns = Integer.parseInt(tokenizer.nextToken());
        int numRoads = Integer.parseInt(tokenizer.nextToken());
        barns = new Barn[numBarns];
        adjacent = new boolean[numBarns][numBarns];
        for (int i = 0; i < numBarns; i++) {
            barns[i] = new Barn(i);
        }
        for (int i = 0; i < numRoads; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            adjacent[first][second] = true;
            adjacent[second][first] = true;
        }
        for (int i = 0; i < numBarns; i++) {
            for (int j = 0; j < numBarns; j++) {
                barns[j].component = -2;
            }
            numComponents = 0;
            for (int j = 0; j < numBarns; j++) {
                if (barns[j].valid && barns[j].component == -2) {
                    barns[j].component = -1;
                    numComponents++;
                    flood_fill();
                }
                if(numComponents > 1){
                    break;
                }
            }
            if(numComponents == 1){
                //System.out.println("YES");
            }
            else{
                //System.out.println("NO");
            }

            int rem = Integer.parseInt(in.readLine()) - 1;
            barns[rem].valid = false;
            for (int j = 0; j < numBarns; j++) {
                adjacent[rem][j] = false;
                adjacent[j][rem] = false;
            }
            
        }
        in.close();
        // out.close();
    }

    public static void flood_fill() {
        int added = 1;
        while (added > 0) {
            added = 0;
            for (int i = 0; i < numBarns; i++) {
                if (barns[i].valid && barns[i].component == -1) {
                    barns[i].component = numComponents;
                    added++;
                    for (int j = 0; j < numBarns; j++) {
                        if (adjacent[i][j] && barns[j].valid && barns[j].component == -2) {
                            barns[j].component = -1;
                        }
                    }
                }
            }
        }
    }

    public static class Barn {
        int id;
        int component = -2;
        boolean valid = true;

        public Barn(int id) {
            this.id = id;
        }
    }
}