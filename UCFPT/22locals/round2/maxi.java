import java.io.*;
import java.util.*;

public class maxi {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int a = Integer.parseInt(in.readLine());
        if (a == 0) {
            System.out.println(0);
        } else {
            ArrayList<Integer> digs = new ArrayList<>();
            while (a > 0) {
                digs.add(a % 10);
                a /= 10;
            }
            Collections.sort(digs);
            for (int i = digs.size() - 1; i >= 0; i--) {
                System.out.print(digs.get(i));
            }
            System.out.println();
        }

    }
}