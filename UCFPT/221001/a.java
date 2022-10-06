import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int s = Integer.parseInt(tokenizer.nextToken()) - 1;
        int m = Integer.parseInt(tokenizer.nextToken());
        int[] a = new int[n];
        boolean[] v = new boolean[n];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(tokenizer.nextToken());
        }
        //v[s] = true;
        int cur = s;
        int hops = 0;
        boolean cycle = false;
        while(cur >= 0 && cur < n && a[cur] != m){
            if(v[cur]){
                cycle = true;
                break;
            }
            v[cur] = true;
            cur += a[cur];
            hops++;
        }
        if(cycle){
            System.out.println("cycle\n" + hops);
        }
        else if(cur < 0){
            System.out.println("left\n" + hops);
        }
        else if(cur >= n){
            System.out.println("right\n" + hops);
        }
        else{
            System.out.println("magic\n" + hops);
        }
        in.close();
    }
}