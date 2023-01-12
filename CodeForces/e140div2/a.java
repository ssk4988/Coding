import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            in.readLine();
            int[][] c = new int[3][2];
            Set<Integer> x = new HashSet<>();
            Set<Integer> y = new HashSet<>();
            for(int i = 0; i < 3; i++){
                String s = in.readLine();
                StringTokenizer tokenizer =new StringTokenizer(s);
                // System.out.println(">" + s + "<");
                c[i][0] = Integer.parseInt(tokenizer.nextToken());
                c[i][1] = Integer.parseInt(tokenizer.nextToken());
                x.add(c[i][0]);y.add(c[i][1]);
            }
            if(x.size() < 3 && y.size() < 3) {
                out.append("NO\n");
                continue;
            }
            else{
                out.append("YES\n");
            }
        }
        System.out.print(out);
        in.close();
    }
}