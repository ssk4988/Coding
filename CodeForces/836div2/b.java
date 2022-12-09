import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out =new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int highestbit = 0;
            while((n & (1 << highestbit)) == 0){
                highestbit++;
            }
            int[] ans = new int[n];
            int ind = 0;
            while(ind < n){
                int k = 1;
                ans[ind++] = k;
                k |= (1 << highestbit);
                for(int j = 0; j < (1 << highestbit) - 1; j++){
                    ans[ind++] = k;
                }
            }
            for(int i = 0; i < n; i++){
                out.append(ans[i]);
                if(i + 1 < n){
                    out.append(" ");
                }
                else{
                    out.append('\n');
                }
            }
        }
        System.out.print(out);
        in.close();
    }
}