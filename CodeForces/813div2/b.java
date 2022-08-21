import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out =new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int[] ans = new int[n];
            for(int i = n-1; i-1 >= 0; i -= 2){
                ans[i] = i-1;
                ans[i-1] = i;
            }
            for(int i = 0; i < n; i++){
                out.append((ans[i]+1) + (i + 1 < n ? " " : "\n"));
            }
        }
        System.out.print(out);
        in.close();
    }
}