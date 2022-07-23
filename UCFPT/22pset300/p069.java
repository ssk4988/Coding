import java.io.*;
import java.util.*;

public class p069 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int m = Integer.parseInt(tokenizer.nextToken());
        int f = Integer.parseInt(tokenizer.nextToken());
        long[] a = new long[f];
        for(int i = 0; i < a.length; i++){
            a[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int n = Integer.parseInt(in.readLine());
        boolean[] works = new boolean[n];
        boolean[][] files = new boolean[n][m];
        for(int i = 0; i < n; i++){
            String s= in.readLine();
            for(int j = 0; j < s.length(); j++){
                int c = Integer.parseInt(s.substring(j, j+1), 16);
                for(int k = 0; k < 4; k++){
                    if(4 * j + k >= m)break;
                    if((c & (1 << k)) > 0) files[i][4*j+k] = true;
                }
            }
        }
        tokenizer =new StringTokenizer(in.readLine());
        int q = Integer.parseInt(tokenizer.nextToken());
        int[] u = new int[q];
        for(int i = 0; i < q; i++){
            u[i] = Integer.parseInt(tokenizer.nextToken());
            boolean[] arr = new boolean[m];
            for(int j=  0; j < f; j++){
                arr[(int)((a[j]*u[i])%m)] = true;
            }
            for(int j = 0; j < works.length; j++){
                if(works[j]) continue;
                works[j] = true;
                for(int k = 0; k < files[j].length; k++){
                    if(arr[k] && !files[j][k]) works[j] = false;
                }
            }
        }
        int cnt = 0;
        StringBuilder b = new StringBuilder();
        for(int i = 0; i < n; i++){
            if(works[i]) cnt++;
        }
        b.append(cnt);
        for(int i = 0; i < n; i++){
            if(works[i]){
                b.append(" " + i);
            }
        }
        System.out.println(b);
        in.close();
    }
}