import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int p = Integer.parseInt(tokenizer.nextToken());
        int low = 1;
        int high = n;
        int x = 1;
        while(test(n, p, x)){
            x++;
        }
        System.out.println(calc(n, p, x));
        /*while(low < high){
            int mid = low + (high - low + 1) / 2;
            if(test(n, p, mid)){
                low = mid;
            }
            else{
                high = mid - 1;
            }
        }*/
        in.close();
        out.close();
    }
    public static double calc(int n, int p, int x){
        double val = p;
        for(int i = 0; i < p-1; i++){
            val *= n-i;
            val /= n + x - i;
        }
        val *= x;
        val /= n + x - (p-1);
        return val;
    }
    public static boolean test(int n, int p, int x){
        double val = x + 1;
        val /= x;
        val *= n + x - (p-1);
        val /= n + x + 1;
        return val >= 1;
    }
}