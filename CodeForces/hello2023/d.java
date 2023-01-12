import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int[] a = new int[n];
            int[] b = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                a[i] = Integer.parseInt(tokenizer.nextToken());
            }
            tokenizer = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                b[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int[] r = new int[n];
        }
        System.out.print(out);
        in.close();
    }
}