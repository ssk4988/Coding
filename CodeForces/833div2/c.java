import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            long[] arr = new long[n];
            ArrayList<Integer> z = new ArrayList<>();
            for(int i = 0; i < n; i++){
                arr[i] = Long.parseLong(tokenizer.nextToken());
                if(arr[i] == 0){
                    z.add(i);
                }
            }
            int index = 0;
            int fb = z.size() > 0 ? z.get(0) : n;
            long running = 0;
            long ans = 0;
            for(; index < fb; index++){
                running += arr[index];
                if(running == 0) ans++;
            }
            for(int i = 0; i < z.size(); i++){
                fb = i + 1 < z.size() ? z.get(i + 1) : n;
                Map<Long, Integer> freq =new HashMap<>();
                long maxKey = 0;
                freq.put(0L, 0);
                for(; index < fb; index++){
                    running += arr[index];
                    if(!freq.containsKey(running)){
                        freq.put(running, 0);
                    }
                    if(freq.get(running) + 1 > freq.get(maxKey)){
                        maxKey = running;
                    }
                    freq.put(running, freq.get(running)+1);
                }
                ans += freq.get(maxKey);
                arr[z.get(i)] = -maxKey;
                running -= maxKey;
            }
            System.out.println(ans);
        }
        in.close();
    }
}