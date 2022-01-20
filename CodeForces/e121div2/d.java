import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] a = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            Set<Integer> set = new TreeSet<>();
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(tokenizer.nextToken());
                set.add(a[i]);
            }
            Map<Integer, Integer> map = new HashMap<>();
            int k = 0;
            for (int s : set) {
                map.put(s, k);
                k++;
            }
            int[] freq = new int[k];
            int[] prefix = new int[k];
            for (int i = 0; i < n; i++) {
                a[i] = map.get(a[i]);
                freq[a[i]]++;
                prefix[a[i]]++;
            }
            for(int i = 0; i+1 < prefix.length; i++){
                prefix[i+1] += prefix[i];
            }
            for(int i = 0; i < prefix.length; i++){

            }
        }

        in.close();
        out.close();
    }
    public static int lowest2(int val){
        int next = val;
        int count = -1;
        while(next > 0){
            count++;
            next >>= 1;
        }
        if(count == -1){
            
        }


        return 0;
    }
}