import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            // CHECK m = 0
            TreeMap<Integer, Integer> ends = new TreeMap<>();
            Map<Integer, ArrayList<Integer>> starts = new HashMap<>();
            for(int i = 0; i < m; i++){
                tokenizer =new StringTokenizer(in.readLine());
                int a = Integer.parseInt(tokenizer.nextToken());
                int b= Integer.parseInt(tokenizer.nextToken());
                a--;b--;
                if(a > b){
                    int tmp = a;
                    a = b;
                    b = tmp;
                }
                if(!starts.containsKey(a)){
                    starts.put(a, new ArrayList<>());
                }
                starts.get(a).add(b);
                if(!ends.containsKey(b)){
                    ends.put(b, 0);
                }
                ends.put(b, ends.get(b) + 1);
            }
            long ans = 0;
            for(int i = 0; i < n; i++){
                int ub = ends.size() == 0 ? n : ends.firstKey();
                ans += ub - i;
                if(starts.containsKey(i)){
                    for(int k : starts.get(i)){
                        ends.put(k, ends.get(k) - 1);
                        if(ends.get(k) == 0){
                            ends.remove(k);
                        }
                    }
                }
                
            }
            out.append(ans + "\n");
        }
        System.out.print(out);
        in.close();
    }
    static class pair{
        int first;
        int second;
        public pair(int first, int second){
            this.first = first;
            this.second = second;
        }

    }
}