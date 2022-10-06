import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //n == 1
        int nc = Integer.parseInt(in.readLine());
        StringBuilder b =new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int[] d =new int[n];
            int[] a = new int[n];
            boolean onlyOne = true;
            for(int i = 0; i < n; i++){
                d[i] = Integer.parseInt(tokenizer.nextToken());
            }
            a[0] = d[0];
            for(int i = 1; i < n; i++){
                if(a[i - 1] - d[i] >= 0 && a[i-1]-d[i] != a[i-1]+d[i]){
                    onlyOne = false;
                }
                a[i] = a[i-1] + d[i];
            }
            if(onlyOne){
                for(int i = 0; i < n; i++){
                    b.append(a[i] + (i + 1 <n ? " " : "\n"));
                }
            }
            else{
                b.append("-1\n");
            }
        }
        System.out.print(b);
        in.close();
    }
}