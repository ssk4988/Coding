import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken()) - 1;
            int ans = 0;
            long[] a = new long[n];
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                a[i] = Integer.parseInt(tokenizer.nextToken());
            }
            long[] pref = new long[n];
            pref[0] = a[0];
            for(int i = 1; i < n; i++){
                pref[i] = pref[i - 1] + a[i];
            }
            long diff = 0;
            TreeMap<Long, Integer> freq = new TreeMap<>();
            for(int i = m + 1; i < n; i++){
                if(a[i] < 0){
                    if(!freq.containsKey(a[i])){
                        freq.put(a[i], 0);
                    }
                    freq.put(a[i], freq.get(a[i]) + 1);
                }
                while(freq.size() > 0 && pref[i] + diff < pref[m]){
                    long highest = freq.firstKey();
                    ans++;
                    diff += -2 * highest;
                    freq.put(highest, freq.get(highest) - 1);
                    if(freq.get(highest).equals(0)){
                        freq.remove(highest);
                    }
                }
            }
            freq.clear();
            for(int i = m; i >= 0; i--){
                while(freq.size() > 0 && pref[i] < pref[m]){
                    long highest = freq.lastKey();
                    ans++;
                    pref[m] -= 2 * highest;
                    freq.put(highest, freq.get(highest) - 1);
                    if(freq.get(highest).equals(0)){
                        freq.remove(highest);
                    }
                }
                if(a[i] > 0){
                    if(!freq.containsKey(a[i])){
                        freq.put(a[i], 0);
                    }
                    freq.put(a[i], freq.get(a[i]) + 1);
                }
            }
            out.append(ans + "\n");
        }
        System.out.print(out);
        in.close();
    }
}