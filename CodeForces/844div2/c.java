import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            String s = in.readLine();
            int[] freq = new int[26];
            ArrayList<Pair> freq1 = new ArrayList<>();
            for(int i = 0; i < n; i++){
                freq[s.charAt(i) - 'a']++;
            }
            for(int i = 0; i < 26; i++){
                Pair p = new Pair();
                p.freq = freq[i];
                p.c = i;
                freq1.add(p);
            }
            Collections.sort(freq1);
            int best = Integer.MAX_VALUE;
            int ind = -1;
            for(int i = 1; i <= 26; i++){
                if(n % i != 0){
                    continue;
                }
                int mad = 0;
                for(int j = freq1.size() - 1; j >= 0; j--){
                    if(freq1.size() - j <= i){
                         mad += Math.abs(n / i - freq1.get(j).freq);
                    }
                    else{
                        mad += freq1.get(j).freq;
                    }
                   
                }
                mad /= 2;
                if(mad < best){
                    best = mad;
                    ind = i;
                }
            }
            int[] rfreq = new int[26];
            for(int i = 0; i < 26; i++){
                rfreq[freq1.get(i).c] = 25-i;
            }
            int numset = 0;
            for(int i = 0; i < 26; i++){
                if(freq[i] == n / ind){
                    numset++;
                }
            }
            char[] ans = s.toCharArray();
            for(int i = 0; i < 26; i++){
                if(freq[i] >= n / ind || rfreq[i] >= ind) continue;
                for(int j = 0; j < n; j++){
                    if(freq[ans[j] - 'a'] > n / ind || rfreq[ans[j] - 'a'] >= ind){
                        freq[ans[j] - 'a']--;
                        ans[j] = (char)('a' + i);
                        freq[ans[j] - 'a']++;
                        if(freq[i] >= n / ind) break;
                    }
                }
                numset++;
            }
            StringBuilder out = new StringBuilder();
            for(int i = 0; i < n; i++){
                out.append(ans[i]);
            }
            System.out.println(best);
            System.out.println(out);
        }
        in.close();
    }
    static class Pair implements Comparable<Pair>{
        int freq;
        int c;
        @Override
        public int compareTo(c.Pair o) {
            return freq - o.freq;
        }
    }
}
