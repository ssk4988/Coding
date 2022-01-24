import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            ArrayList<ram> rams = new ArrayList<>();
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                rams.add(new ram(Integer.parseInt(tokenizer.nextToken()), 0));
            }
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                rams.get(i).reward = Integer.parseInt(tokenizer.nextToken());
            }
            Collections.sort(rams);
            int curr = k;
            for (int i = 0; i < n; i++) {
                if (rams.get(i).cost <= curr) {
                    curr += rams.get(i).reward;
                }
            }
            System.out.println(curr);
        }

        in.close();
        out.close();
    }

    public static class ram implements Comparable<ram> {
        int cost;
        int reward;

        public ram(int cost, int reward) {
            this.cost = cost;
            this.reward = reward;
        }

        @Override
        public int compareTo(a.ram o) {
            if (this.cost == o.cost)
                return o.reward - this.reward;
            return this.cost - o.cost;
        }
    }
}