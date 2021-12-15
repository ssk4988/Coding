import java.io.*;
import java.util.*;

public class genome {
    public static int MOD = 1000000007;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int casenum = Integer.parseInt(in.readLine());
        for (int i = 0; i < casenum; i++) {
            String[] gString = new String[4];
            gene[] genes = new gene[4];
            for (int j = 0; j < 4; j++) {
                gString[j] = in.readLine();
                genes[j] = strToGene(gString[j]);
                genes[j].days = 1;
            }
            String input = in.readLine();
            gene origin = strToGene(input);
            long days = Long.parseLong(in.readLine());
            long day2 = days;
            int maxTimes = 0;
            while (day2 > 0) {
                day2 >>= 1;
                maxTimes++;
            }
            gene[][] propagate = new gene[maxTimes][4];
            propagate[0] = genes;
            for (int j = 1; j < propagate.length; j++) {
                for (int k = 0; k < 4; k++) {
                    propagate[j][k] = propagate[j - 1][k].copy();
                    propagate[j][k].propagate(propagate[j - 1]);
                }
            }
            // for(int j = 0; j < 4; j++){
            // System.out.println(propagate[maxTimes-1][j]);
            // }
            day2 = days;
            long bit = 1;
            int shift = 0;
            while (bit <= days) {
                if ((bit & days) == bit) {
                    origin.propagate(propagate[shift]);
                }
                bit <<= 1;
                shift++;
            }
            System.out.printf("Genome #%d: %d %d %d %d%n", (i+1), origin.map[0], origin.map[1], origin.map[2], origin.map[3]);
        }

        in.close();
        out.close();
    }

    public static gene strToGene(String s) {
        gene g = new gene();
        String d = "ACTG";
        for (int i = 0; i < s.length(); i++) {
            g.map[d.indexOf(s.charAt(i))]++;
        }
        return g;
    }

    public static class gene {
        long days = 0;
        long[] map = new long[4];

        public void propagate(gene[] genes) {
            long[] map2 = new long[4];
            for (int i = 0; i < 4; i++) {// each of map
                for (int j = 0; j < 4; j++) {// each gene
                    map2[i] += map[j] * genes[j].map[i];
                    map2[i] %= MOD;
                }
            }
            days += genes[0].days;
            map = map2;
        }

        @Override
        public String toString() {
            return days + " " + Arrays.toString(map);
        }

        public gene copy() {
            gene g = new gene();
            g.days = days;
            for (int i = 0; i < 4; i++) {
                g.map[i] = map[i];
            }
            return g;
        }
    }
}