import java.io.*;
import java.util.*;

public class secret {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            String[] input = new String[n];
            for(int i = 0; i < n; i++){
                input[i] = in.readLine();
            }
            StringTokenizer tokenizer =new StringTokenizer(in.readLine(), ",");
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            int n2 = Integer.parseInt(in.readLine());
            for(int i = 0; i < n2; i++){
                String s = in.readLine();
                for(int j= 0;j < s.length(); j++){
                    if(s.charAt(j) == 'O'){
                        b.append(input[x+i].charAt(j+y));
                    }
                }
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}