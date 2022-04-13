import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int nt = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        long[] maxp = new long[c + 1];
        for (int i = 0; i < nt; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int c1 = Integer.parseInt(tokenizer.nextToken());
            long d1 = Integer.parseInt(tokenizer.nextToken());
            long h1 = Integer.parseInt(tokenizer.nextToken());
            maxp[c1] = Math.max(maxp[c1], d1 * h1);
        }
        for (int i = 1; i < maxp.length; i++) {
            for(int j = 1; j * i < maxp.length; j++){
                maxp[j*i] = Math.max(maxp[j*i], maxp[i] * j);
            }
        }
        for (int i = 1; i < maxp.length; i++) {
            maxp[i] = Math.max(maxp[i], maxp[i - 1]);
        }
        //System.out.println(Arrays.toString(maxp));
        int nm = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int i = 0; i < nm; i++){
            tokenizer = new StringTokenizer(in.readLine());
            long v = Long.parseLong(tokenizer.nextToken()) * Long.parseLong(tokenizer.nextToken());
            int low = 1;
            int high = c+1;
            while(low < high){
                int mid = low + (high - low) / 2;
                if(maxp[mid] > v){
                    high = mid;
                }
                else{
                    low = mid + 1;
                }
            }
            b.append((low > c ? -1 : low) + " ");
        }
        System.out.println(b);

        in.close();
        out.close();
    }
}