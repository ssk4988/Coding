import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int dishes = Integer.parseInt(tokenizer.nextToken());
            int votes = Integer.parseInt(tokenizer.nextToken());
            int[] t = new int[dishes];
            int[] v = new int[dishes];
            dish[] d = new dish[dishes];
            for(int i = 0; i < dishes; i++){
                tokenizer =new StringTokenizer(in.readLine());
                t[i] = Integer.parseInt(tokenizer.nextToken());
                v[i] = Integer.parseInt(tokenizer.nextToken());
                d[i] = new dish(t[i], v[i]);
            }
            Arrays.sort(d, new comp1());

            /*
            for(int i = 0; i < dishes; i++){
                for(int j = 0; j < dp.length; j++){
                    int i2 = Math.min(j + v[i], votes);
                    if(dp[j] == Integer.MAX_VALUE || (dp[i2] > dp[j] + t[i])){
                        dp[i2] = dp[j] + t[i];
                    }
                }
            }
            System.out.println(dp[votes]);*/
        }
        in.close();
        out.close();
    }
    public static class comp1 implements Comparator <dish>{
        @Override
        public int compare(d.dish o1, d.dish o2) {
            if(o1.ratio == o2.ratio) return 0;
            if(o1.ratio < o2.ratio) return -1;
            return 1;
        }
    }
    public static class comp2 implements Comparator<dish>{
        @Override
        public int compare(d.dish o1, d.dish o2) {
            if(o1.time == o2.time) return o1.votes - o2.votes;
            if(o1.time < o2.time) return -1;
            return 1;
        }
    }
    public static class dish{
        int time;
        int votes;
        double ratio = 0;
        public dish(int time, int votes){
            this.time = time;
            this.votes = votes;
            ratio = (double)votes / time;
        }
    }
}