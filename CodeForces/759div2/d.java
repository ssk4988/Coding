import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int len =Integer.parseInt(in.readLine());
            int[] arr = new int[len];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            Set<Integer> el = new HashSet<>();
            for(int i = 0; i < len; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken())-1;
                el.add(arr[i]);
            }
            if(el.size() < len){
                System.out.println("YES");
                continue;
            }
            boolean[] visited = new boolean[len];
            int inv = 0;
            for(int i = 0; i < len; i++){
                if(visited[i]) continue;
                int cycleLen = 0;
                int cur = i;
                while(!visited[cur]){
                    visited[cur] = true;
                    cycleLen++;
                    cur = arr[cur];
                }
                inv += cycleLen - 1;
            }
            System.out.println(inv % 2 == 0 ? "YES" : "NO");
        }

        in.close();
        out.close();
    }
}