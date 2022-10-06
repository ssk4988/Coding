import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out =new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int[] b = new int[n + 2];
            ArrayList<Integer>[] c = new ArrayList[n + 2];
            for(int i = 0; i < c.length; i++){
                c[i] = new ArrayList<>();
            }
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int i = 1; i <= n; i++){
                b[i] = Integer.parseInt(tokenizer.nextToken());
                c[b[i]].add(i);
            }
            ArrayList<Integer> a = new ArrayList<>();
            int exclude = n + 1;
            int include = 0;
            boolean higher = false;
            int cur = -1;
            if(c[0].size() > 0){
                cur = 0;
                higher = true;
            }
            else if(c[n+1].size()>0){
                cur = n+1;
                higher = false;
            }
            while(a.size() < n){
                int next = -1;
                for(int i : c[cur]){
                    if(c[i].size() > 0) next = i;
                    else a.add(i);

                    if(higher){
                        exclude = Math.min(exclude, i);
                    }
                    else{
                        include = Math.max(include, i);
                    }
                }
                if(next != -1) a.add(next);
                else break;
                cur = next;
                higher = !higher;
            }
            out.append(include + "\n");
            for(int i = 0; i < a.size(); i++){
                out.append(a.get(i));
                out.append(i + 1 < n ? " " : "\n");
            }
        }
        System.out.print(out);
        in.close();
    }
}