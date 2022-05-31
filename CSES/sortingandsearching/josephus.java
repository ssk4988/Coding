import java.io.*;
import java.util.*;

public class josephus {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        TreeSet<Integer> set = new TreeSet<>();
        StringBuilder b = new StringBuilder();
        for (int i = 1; i <= n; i++) {
            set.add(i);
        }
        Integer point = set.last();
        while (set.size() > 0) {
            for (int i = 0; i < 2; i++) {
                point = set.higher(point);
                if (point == null)
                    point = set.first();
            }
            b.append(point);
            set.remove(point);
            b.append(set.size() > 0 ? " " : "\n");
        }
        System.out.print(b);
        in.close();
    }
}