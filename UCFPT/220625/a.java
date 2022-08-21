import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < n; i++) {
            int l = Integer.parseInt(in.readLine());
            int ans = 1 + (l + 1) / 2;
            b.append(ans + "\n");
        }
        System.out.print(b);
        in.close();
    }
}