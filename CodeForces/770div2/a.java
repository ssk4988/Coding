import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int len = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            String s = in.readLine();
            boolean isPal = true;
            for(int i = 0; i < s.length(); i++){
                if(s.charAt(i) != s.charAt(s.length() - 1 - i)){
                    isPal = false;
                    break;
                }
            }
            if(k == 0){
                System.out.println(1);
                continue;
            }
            else{
                int cnt = isPal ? 1 : 2;
                k--;
                System.out.println(cnt);
            }
        }

        in.close();
        out.close();
    }
}