import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int a = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int gcd = gcd(a, b);
        int bal = a * b / gcd;
        if(bal <= c){
            System.out.println("yes");
        }
        else{
            System.out.println("no");
        }

        in.close();
        out.close();
    }
    public static int gcd(int a, int b){
        if(b > a) return gcd(b, a);
        if(b == 0) return a;
        return gcd(b, a % b);
    }
}