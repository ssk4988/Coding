import java.io.*;
import java.util.*;

public class divide {
    static long ans = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        ArrayList<Integer> a = new ArrayList<>();
        Map<Integer, Integer> map = new HashMap<>();
        TreeSet<Integer> set =new TreeSet<>();
        for (int i = 0; i < n; i++) {
            a.add(Integer.parseInt(tokenizer.nextToken()));
            if (!map.containsKey(a.get(i))) {
                map.put(a.get(i), 0);
            }
            map.put(a.get(i), map.get(a.get(i)) + 1);
            set.add(a.get(i));
        }
        Collections.sort(a);
        for(int i : set){
            if(i == 0)continue;
            int cnt = map.get(i);
            for(int j = 2* i; j <=a.get(n-1); j += i){
                if(map.containsKey(j)){
                    ans += map.get(j)*cnt;
                }
            }
        }
        if(map.containsKey(0)){
            ans += map.get(0)*(n-map.get(0));
        }
        System.out.println(ans);
        in.close();
    }
}
