import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] t = new int[n];
        int[] d = new int[n];
        int max = 0;
        for(int i = 0; i < n; i++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            t[i] = Integer.parseInt(tokenizer.nextToken());
            d[i] = Integer.parseInt(tokenizer.nextToken());
            if(i > 0){
                max = Math.max(max, (d[i] - d[i-1])/(t[i] - t[i-1]));
            }
        }
        System.out.println(max);

        in.close();
        out.close();
    }
}