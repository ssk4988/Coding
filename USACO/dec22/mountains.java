import java.io.*;
import java.util.*;

public class mountains {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        long[] h = new long[n];
        TreeSet<Integer>[] seen = new TreeSet[n];
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        for(int i = 0; i < n; i++){
            h[i] = Integer.parseInt(tokenizer.nextToken());
            seen[i] = new TreeSet<>();
        }
        long ans = 0;
        for(int i = 0; i < n; i++){
            int best = -1;
            for(int j = i + 1; j < n; j++){
                if(best == -1 || (h[j] - h[i]) * (best - i) >= (h[best] - h[i]) * (j - i)){
                    ans++;
                    best = j;
                    seen[i].add(j);
                }
            }
        }
        int nq = Integer.parseInt(in.readLine());
        for(int i = 0; i < nq; i++){
            tokenizer =new StringTokenizer(in.readLine());
            int ind = Integer.parseInt(tokenizer.nextToken());
            int v = Integer.parseInt(tokenizer.nextToken());
            ind--;
            h[ind] += v;
            for(int k = 0; k < ind; k++){
                boolean added = false;
                if(seen[k].lower(ind) == null){
                    seen[k].add(ind);
                    added = true;
                }
                else{
                    int l = seen[k].lower(ind);
                    if((h[ind] - h[k]) * (l - k) >= (h[l] - h[k]) * (ind - k)){
                        seen[k].add(ind);
                        added = true;
                    }
                }
                if(added){
                    while(seen[k].higher(ind) != null){
                        int l = seen[k].higher(ind);
                        if((h[ind] - h[k]) * (l - k) > (h[l] - h[k]) * (ind - k)){
                            seen[k].remove(l);
                        }
                        else{
                            break;
                        }
                    }
                }
            }
            seen[ind].clear();
            int best = -1;
            for(int j = ind + 1; j < n; j++){
                if(best == -1 || (h[j] - h[ind]) * (best - ind) >= (h[best] - h[ind]) * (j - ind)){
                    ans++;
                    best = j;
                    seen[ind].add(j);
                }
            }
            ans = 0;
            for(int j = 0; j < n; j++){
                ans += seen[j].size();
            }
            System.out.println(ans);
        }
        
        in.close();
    }
}