import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<Long>[] b = new ArrayList[2];
            for (int i = 0; i < 2; i++) {
                b[i] = new ArrayList<>();
            }
            int[] type = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                type[i] = Integer.parseInt(tokenizer.nextToken());
            }
            tokenizer = new StringTokenizer(in.readLine());
            long damage = 0;
            for (int i = 0; i < n; i++) {
                long dmg = Long.parseLong(tokenizer.nextToken());
                b[type[i]].add(dmg);
                damage += dmg;
            }
            Collections.sort(b[0]);
            Collections.sort(b[1]);

            if (b[0].size() == b[1].size()) {
                damage *= 2;
                damage -= Math.min(b[0].get(0), b[1].get(0));
            } else if (b[0].size() < b[1].size()) {
                for (int i = 0; i < b[0].size(); i++) {
                    damage += b[1].get(b[1].size() - 1 - i);
                }
                for(long k : b[0]){
                    damage += k;
                }
            }
            else{
                for (int i = 0; i < b[1].size(); i++) {
                    damage += b[0].get(b[0].size() - 1 - i);
                }
                for(long k : b[1]) damage += k;
            }
            out.append(damage + "\n");
        }
        System.out.print(out);
    }
}