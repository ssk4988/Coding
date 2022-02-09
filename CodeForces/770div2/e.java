import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int arrays = Integer.parseInt(in.readLine());
        array[] as = new array[arrays];
        boolean valid = true;
        Map<Integer, pair> map = new HashMap<>();
        Map<Integer, Integer> freq = new HashMap<>();
        for (int i = 0; i < arrays; i++) {
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] arr = new int[n];
            for (int j = 0; j < n; j++) {
                arr[j] = Integer.parseInt(tokenizer.nextToken());
            }
            as[i] = new array(arr);
            if (!as[i].valid) {
                valid = false;
                break;
            }
            for (int j = 0; j < arr.length; j++) {
                if (!freq.containsKey(arr[j])) {
                    freq.put(arr[j], 0);
                }
                freq.put(arr[j], freq.get(arr[j]) + 1);
            }
            for (int k : as[i].unused) {
                int val = as[i].a[k];
                if (!map.containsKey(val)) {
                    map.put(val, null);
                }
                pair p = map.get(val);
                if (p == null) {
                    map.put(val, as[i].p[k]);
                } else {
                    p.p = as[i].p[k];
                    as[i].p[k].p = p;
                    map.put(val, null);
                }
            }
        }
        for (int i : freq.keySet()) {
            if (freq.get(i) % 2 == 1) {
                valid = false;
                return;
            }
        }
        for (int i = 0; i < as.length; i++) {
            while (as[i].unused.size() > 0) {
                pair cur = as[i].p[as[i].unused.first()];
                boolean l = as[i].lcnt > as[i].rcnt ? false : true;
                cur.a.unused.remove(cur.index);
                cur.a.left[cur.index] = l;
                if (l)
                    cur.a.lcnt++;
                else
                    cur.a.rcnt++;
                l = !l;
                cur = cur.p;
                cur.a.unused.remove(cur.index);
                cur.a.left[cur.index] = l;
                if (l)
                    cur.a.lcnt++;
                else
                    cur.a.rcnt++;
                l = !l;
                while (cur.a.unused.size() > 0) {
                    cur = cur.a.p[as[i].unused.first()];
                    cur.a.unused.remove(cur.index);
                    cur.a.left[cur.index] = l;
                    if (l)
                        cur.a.lcnt++;
                    else
                        cur.a.rcnt++;
                    l = !l;
                    cur = cur.p;
                    cur.a.unused.remove(cur.index);
                    cur.a.left[cur.index] = l;
                    if (l)
                        cur.a.lcnt++;
                    else
                        cur.a.rcnt++;
                    l = !l;
                }
            }
        }
        for(array a : as){
            if(a.lcnt != a.rcnt){
                valid = false;
            }
        }
        if (!valid) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
            for (array a : as) {
                for (int i = 0; i < a.a.length; i++) {
                    if (a.unused.contains(i)) {
                        System.out.print("_");
                    } else {
                        System.out.print(a.left[i] ? "L" : "R");
                    }
                }
                System.out.println();
            }
        }

        in.close();
        out.close();
    }

    public static class array {
        int id;
        int[] a;
        pair[] p;
        boolean[] left;
        TreeSet<Integer> unused = new TreeSet<>();
        Map<Integer, Integer> freq = new HashMap<>();
        boolean valid = true;
        int lcnt = 0;
        int rcnt = 0;

        public array(int[] a) {
            this.a = a;
            left = new boolean[a.length];
            p = new pair[a.length];
            for (int i = 0; i < a.length; i++) {
                unused.add(i);
                if (!freq.containsKey(a[i])) {
                    freq.put(a[i], 0);
                }
                freq.put(a[i], freq.get(a[i]) + 1);
                p[i] = new pair(a[i], this, i);
            }
            /*
             * for(int i : freq.keySet()){
             * if(freq.get(i)%2 == 1){
             * valid = false;
             * return;
             * }
             * }
             */
            Map<Integer, Integer> used = new HashMap<>();
            for (int i = 0; i < a.length; i++) {
                if (!used.containsKey(a[i])) {
                    used.put(a[i], 0);
                }
                if (freq.get(a[i]) - used.get(a[i]) <= 1 && freq.get(a[i]) % 2 == 1) {
                    continue;
                }
                if (freq.get(a[i]) % 2 == 0) {
                    left[i] = (freq.get(a[i]) - used.get(a[i])) % 2 == 0;
                } else {
                    left[i] = (freq.get(a[i]) - used.get(a[i])) % 2 == 1;
                }
                if (left[i])
                    lcnt++;
                else
                    rcnt++;
                used.put(a[i], used.get(a[i]) + 1);
                unused.remove(i);
            }
        }
    }

    public static class pair {
        int val;
        int index;
        pair p = null;
        array a = null;

        public pair(int val, array a, int index) {
            this.val = val;
            this.a = a;
            this.index = index;
        }
    }
}