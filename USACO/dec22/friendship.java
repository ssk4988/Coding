import java.io.*;
import java.util.*;

public class friendship {
    static HashSet<Integer>[] adj;
    static long ans = 0;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        adj = new HashSet[n];
        HashSet<Integer> tot = new HashSet<>();
        for(int i = 0; i < n; i++){
            adj[i] = new HashSet<>();
            tot.add(i);
        }
        for(int i = 0; i < m; i++){
            tokenizer =new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }
        for(int i = 0; i < n; i ++){
            if(!tot.contains(i)){
                continue;
            }
            HashSet<Integer> component = new HashSet<>();
            ArrayDeque<Integer> q = new ArrayDeque<>();
            component.add(i);
            tot.remove(i);
            q.add(i);
            while(!q.isEmpty()){
                int k = q.poll();
                for(int l : adj[k]){
                    if(!component.contains(l)){
                        component.add(l);
                        tot.remove(l);
                        q.add(l);
                    }
                }
            }
            solve(component);
        }
        System.out.println(ans);

        in.close();
    }
    static void solve(HashSet<Integer> component){
        int minFriends = Integer.MAX_VALUE;
        for(int i : component){
            minFriends = Math.min(minFriends, adj[i].size());
        }
        ans = Math.max(minFriends * component.size(), ans);
        ArrayDeque<Integer> rem = new ArrayDeque<>();
        ArrayList<Integer> r = new ArrayList<>();
        for(int i : component){
            if(adj[i].size() <= minFriends){
                rem.add(i);
                r.add(i);
            }
        }
        component.removeAll(r);
        while(!rem.isEmpty()){
            int i = rem.poll();
            for(int j : adj[i]){
                adj[j].remove(i);
                if(component.contains(j) && adj[j].size() <= minFriends){
                    component.remove(j);
                    rem.add(j);
                }
            }
            adj[i].clear();
        }
        HashSet<Integer> removed = new HashSet<>();
        for(int i : component){
            if(removed.contains(i)) continue;
            HashSet<Integer> newcomp = new HashSet<>();
            ArrayDeque<Integer> q = new ArrayDeque<>();
            newcomp.add(i);
            removed.add(i);
            q.add(i);
            while(!q.isEmpty()){
                int k = q.poll();
                for(int l : adj[k]){
                    if(!newcomp.contains(l)){
                        newcomp.add(l);
                        removed.add(l);
                        q.add(l);
                    }
                }
            }
            solve(newcomp);
        }
    }
}