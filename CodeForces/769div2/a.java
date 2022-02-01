import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            String s = in.readLine();
            int[] cnt = new int[2];
            for(int i = 0; i < n; i++){
                cnt[s.charAt(i)-'0']++;
            }
            if((cnt[0]<=1&&cnt[1]<=1)){
                System.out.println("YES");
            }
            else{
                System.out.println("NO");
            }
        }

        in.close();
        out.close();
    }
}