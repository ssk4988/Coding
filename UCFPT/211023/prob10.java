/*
ID: ssk49881
LANG: JAVA
TASK: prob10
*/

import java.io.*;
import java.util.*;

public class prob10 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        Map<Integer, Integer> xmap = new HashMap<>();
        Map<Integer, Integer> ymap = new HashMap<>();
        int numx = 0;
        int numy = 0;
        int m = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int[] mx = new int[m];
        int[] my = new int[m];
        int[] cx = new int[c];
        int[] cy = new int[c];
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if (!xmap.containsKey(x)) {
                xmap.put(x, numx);
                numx++;
            }
            if (!ymap.containsKey(y)) {
                ymap.put(y, numy);
                numy++;
            }
            mx[i] = xmap.get(x);
            my[i] = ymap.get(y);
        }
        for (int i = 0; i < c; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if (!xmap.containsKey(x)) {
                xmap.put(x, numx);
                numx++;
            }
            if (!ymap.containsKey(y)) {
                ymap.put(y, numy);
                numy++;
            }
            cx[i] = xmap.get(x);
            cy[i] = ymap.get(y);
        }
        int[] mnumx = new int[numx];
        int[] mnumy = new int[numy];
        int[] cnumx = new int[numx];
        int[] cnumy = new int[numy];
        for (int i = 0; i < mx.length; i++) {
            mnumx[mx[i]]++;
            mnumy[my[i]]++;
        }
        Set<Integer> cindices = new HashSet<>();
        for (int i = 0; i < c; i++) {
            if (mnumx[cx[i]] < 2 && mnumy[cy[i]] < 2) {
                cnumx[cx[i]]++;
                cnumy[cy[i]]++;
            }

            cindices.add((cx[i] << 6) + cy[i]);
        }
        int max = -1;
        int besti = -1;
        int bestj = -1;
        Map<Integer, Integer> reversexmap = new HashMap<>();
        Map<Integer, Integer> reverseymap = new HashMap<>();
        for (Map.Entry<Integer, Integer> entry : xmap.entrySet()) {
            reversexmap.put(entry.getValue(), entry.getKey());
        }
        for (Map.Entry<Integer, Integer> entry : ymap.entrySet()) {
            reverseymap.put(entry.getValue(), entry.getKey());
        }
        for (int i = 0; i < cnumx.length; i++) {
            for (int j = 0; j < cnumy.length; j++) {
                int t = 0;
                if (mnumx[i] == 1) {
                    t += cnumx[i];
                }
                if (mnumy[j] == 1) {
                    t += cnumy[j];
                }
                if (mnumx[i] == 1 && mnumy[j] == 1) {
                    if (cindices.contains((i << 6) + j)) {
                        t--;
                    }
                }

                // System.out.println(reversexmap.get(i) + " " + reverseymap.get(j) + " " + t);
                if (t > max) {
                    max = t;
                    besti = i;
                    bestj = j;
                }
            }
        }
        System.out.println(reversexmap.get(besti) + " " + reverseymap.get(bestj));
        System.out.println(max);

        in.close();
        out.close();
    }
}