import java.io.*;
import java.util.*;

public class collectingnumbers2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        int[] arr = new int[n];
        int[] rev = new int[n];
        int cnt = 1;
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
            rev[arr[i]] = i;
        }
        for (int i = 0; i < n-1; i++) {
            if(rev[i+1]<rev[i]) cnt++;
        }
        StringBuilder b = new StringBuilder();
        // System.out.println(cnt);
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int[] a = new int[2];
            Set<Integer> check = new HashSet<>();
            for (int j = 0; j < 2; j++) {
                a[j] = Integer.parseInt(tokenizer.nextToken()) - 1;
                if (arr[a[j]] - 1 >= 0)
                    check.add(arr[a[j]] - 1);
                if (arr[a[j]] + 1 < n)
                    check.add(arr[a[j]]);
            }
            for (int c : check) {
                if (rev[c] > rev[c + 1]) {
                    cnt--;
                }
            }
            rev[arr[a[0]]] = a[1];
            rev[arr[a[1]]] = a[0];
            int tmp = arr[a[0]];
            arr[a[0]] = arr[a[1]];
            arr[a[1]] = tmp;
            for (int c : check) {
                if (rev[c] > rev[c + 1]) {
                    cnt++;
                }
            }
            b.append(cnt + "\n");
        }
        System.out.print(b);
        in.close();
    }
}