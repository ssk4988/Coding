import java.io.*;
import java.util.*;

public class p065 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int a = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        ing[] g = new ing[n];
        ing[] g2 = new ing[n];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            g[i] = new ing(Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()),
                    Integer.parseInt(tokenizer.nextToken()));
                    g2[i] = g[i];
        }
        Arrays.sort(g);
        double a1 = 0;
        double b1 = 0;
        for (int i = 0; i < n; i++) {
            g[i].used = Math.min(g[i].max, (g[i].b == 0 ? g[i].max : (b - b1) / g[i].b));
            a1 += g[i].used * g[i].a;
            b1 += g[i].used * g[i].b;
            if(g[i].used != g[i].max) break;
        }
        if(a1 < a){
            System.out.println("-1 -1");
        }
        else{
            StringBuilder out = new StringBuilder();
            out.append(a1 + " " + b1 + "\n");
            for(int i = 0;i < n; i++){
                out.append(g2[i].used + (i + 1 < n ? " " : "\n"));
            }
            System.out.print(out);
        }
        in.close();
    }

    public static class ing implements Comparable<ing> {
        int max;
        double used = 0;
        int a = 0;
        int b = 0;
        double ratio = 0;

        public ing(int max, int a, int b) {
            this.max = max;
            this.a = a;
            this.b = b;
            if (b == 0) {
                if (a == 0) {
                    ratio = 0;
                } else {
                    ratio = 1000;
                }
            } else {
                ratio = (double) a / b;
            }
        }

        @Override
        public int compareTo(p065.ing o) {
            if (o.ratio > this.ratio)
                return 1;
            if (o.ratio < this.ratio)
                return -1;
            return 0;
        }
    }
}