import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            ArrayList<Integer> a = new ArrayList<>();
            for(int i = 0; i < n; i++){
                a.add(Integer.parseInt(tokenizer.nextToken()));
            }
            Collections.sort(a);
            int ans = 0;
            int point = 0;
            int cur = -1;
            while(point < n){
                while(point < n && (point <= cur || a.get(point) <= point)){
                    cur = a.get(point);
                    point++;
                }
                //System.out.println("at + " + point);
                ans++;
                if(point < n) cur = a.get(point);
                point++;
            }
            System.out.println(ans);
        }
        in.close();
    }
}
