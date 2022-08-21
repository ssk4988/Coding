import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            tokenizer = new StringTokenizer(in.readLine());
            ArrayList<Integer> a = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                int v = Integer.parseInt(tokenizer.nextToken());
                a.add(v);
            }
            int low = 0;
            int high = 1000000000;
            while (low < high) {
                int mid = low + (high - low + 1) / 2;
                if (test(a, mid) <= k) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            System.out.println(low);
        }
        in.close();
    }

    public static int test(ArrayList<Integer> a, int val) {
        ArrayList<Integer> arr = cp(a);
        int cnt = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr.get(i) * 2 < val) {
                arr.set(i, 1000000000);
                cnt++;
            }
        }
        for (int i = 0; i + 1 < arr.size(); i++) {
            if (Math.min(arr.get(i), arr.get(i + 1)) >= val) {
                return cnt;
            }
        }
        for (int i = 0; i + 1 < arr.size(); i++) {
            if (Math.min(arr.get(i), arr.get(i + 1)) < val && Math.max(arr.get(i), arr.get(i + 1)) >= val) {
                if (arr.get(i) < arr.get(i + 1)) {
                    arr.set(i, 1000000000);
                    cnt++;
                } else {
                    arr.set(i + 1, 1000000000);
                    cnt++;
                }
                return cnt;
            }
        }
        for (int i = 0; i + 1 < arr.size(); i++) {
            if (Math.max(arr.get(i), arr.get(i + 1)) < val) {
                arr.set(i, 1000000000);
                cnt++;

                arr.set(i + 1, 1000000000);
                cnt++;
                return cnt;
            }
        }
        return cnt;
    }

    public static ArrayList<Integer> cp(ArrayList<Integer> arr) {
        ArrayList<Integer> a = new ArrayList<>();
        for (int i = 0; i < arr.size(); i++) {
            a.add(arr.get(i));
        }
        return a;
    }
}