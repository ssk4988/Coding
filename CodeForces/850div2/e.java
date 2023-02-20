import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            ArrayList<Integer> a =new ArrayList<>();
            for(int i = 0; i < n; i++){
                a.add(Integer.parseInt(tokenizer.nextToken()));
            }
            Collections.sort(a);
            long ans = 0;
            int curseries = 0;
            for(int i = 0; i < n; i++){
                if(a.get(i) > curseries + 1){
                    int cnt = a.get(i) - (curseries + 1);
                    ans+= cnt;
                    a.set(i, a.get(i) - cnt);
                }
                curseries = Math.max(curseries, a.get(i));
            }
            System.out.println(ans);
        }
        in.close();
    }
}
