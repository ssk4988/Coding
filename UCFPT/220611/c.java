import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        long k = Long.parseLong(in.readLine());
        int[] parent = new int[200001];
        Arrays.fill(parent, -1);
        int cur = 0;
        parent[cur] = 0;
        while (k > 4) {
            if (k % 2 == 1) {
                parent[cur + 1] = cur;
                parent[cur+2] = cur;
                cur += 2;
                k /= 2;
            } else {
                parent[cur + 1] = cur;
                cur++;
                k--;
            }
        }
        k -= 2;
        for (int i = 0; i < k; i++) {
            parent[cur + 1] = cur;
            cur++;
        }
        int cnt = cur + 1;
        StringBuilder ans = new StringBuilder();
        ans.append(cnt + "\n");
        for (int i = 1; i < cnt; i++) {
            ans.append((parent[i] + 1) + " " + (i + 1) + "\n");
        }
        System.out.print(ans);
        in.close();
    }
}