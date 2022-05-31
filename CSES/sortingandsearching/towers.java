import java.io.*;
import java.util.*;

public class towers {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        TreeMap<Integer, Integer> map = new TreeMap<>();
        for (int i = 0; i < n; i++) {
            int c = Integer.parseInt(tokenizer.nextToken());
            Integer h = map.higherKey(c);
            if (h != null) {
                if (map.get(h) == 1) {
                    map.remove((int) h);
                } else {
                    map.put(h, map.get(h) - 1);
                }
            }
            if (!map.containsKey(c)) {
                map.put(c, 0);
            }
            map.put(c, map.get(c) + 1);
        }
        int cnt = 0;
        for (Integer c : map.keySet()) {
            cnt += map.get(c);
        }
        System.out.println(cnt);
        in.close();
    }
}