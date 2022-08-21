import java.io.*;
import java.lang.reflect.Array;
import java.util.*;
 
public class E847 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        String s = in.readLine();
        ArrayList<Integer> pack = new ArrayList<>();
        ArrayDeque<Integer> food = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == 'P')
                pack.add(i);
            if (s.charAt(i) == '*')
                food.add(i);
        }
        int low = 0;
        int high = Integer.MAX_VALUE;
        while (low < high) {
            int mid = low + (high - low) / 2;
            ArrayDeque<Integer> f = new ArrayDeque<>();
            f.addAll(food);
            if (solve(f, pack, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        b.append(low + "\n");
 
        System.out.print(b);
        in.close();
    }
 
    public static boolean solve(ArrayDeque<Integer> food, ArrayList<Integer> pack, int val) {
        outer: for (int p : pack) {
            int l = 0;
            int r = 0;
            int l1 = 0;
            int r1 = 0;
            while (food.size() > 0) {
                int next = food.getFirst();
                l1 = l;
                r1 = r;
                if (next <= p) {
                    int f = next;
                    l1 = Math.max(p - f, l1);
                    food.removeFirst();
                    if (l1 + r1 + Math.min(l1, r1) > val)
                        return false;
                } else  {
                    int c = next;
                    r1 = Math.max(c - p, r1);
 
                    if (l1 + r1 + Math.min(l1, r1) > val) {
                        continue outer;
                    } else {
                        food.removeFirst();
                    }
                }
                l = l1;
                r = r1;
            }
        }
        return food.size() == 0;
    }
}