import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int p = Integer.parseInt(tokenizer.nextToken());
        int q = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        double target = (double)p / q;
        boolean found = false;
        outer: for(int i = n; i <= m; i++){
            for(int r = 0; r <= i-r; r++){
                int g = i - r;
                double v = (double)2 * r / i * g / (i-1);
                if(Math.abs(v - target) < 1e-9){
                    System.out.println(r + " " + g);
                    found = true;
                    break outer;
                }
                
            }
        }
        if(!found){
            System.out.println("NO SOLUTION");
        }

        in.close();
        out.close();
    }
}