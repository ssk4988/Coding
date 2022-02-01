import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int max2 = Integer.highestOneBit(n);
        int numsparse = Integer.numberOfTrailingZeros(max2) + 1;
        int[][] sparse = new int[numsparse][n];
        int[] arr = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            sparse[0][i] = arr[i] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 1; i < sparse.length; i++) {
            int interval = 1 << i;
            for (int j = 0; j < sparse[i].length; j++) {
                sparse[i][j] = sparse[i - 1][j];
                if (j + interval - 1 < sparse[i].length) {
                    sparse[i][j] = gcd(sparse[i][j], sparse[i][j + interval - 1]);
                }
            }
        }

        int replace = 1000000007;
        int lastp = -1;
        int total = 0;
        ArrayList<Integer> list = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int length = 0;
            list.add(arr[i]);
            for (int j = list.size() - 1; j >= 0; j--) {
                list.set(j, gcd(list.get(j), arr[i]));
                length++;
                if (length == list.get(j)) {
                    total++;
                    lastp = i;
                    arr[i] = replace;
                    list = new ArrayList<>();
                    break;
                }
                if (length > list.get(j)) {
                    break;
                }
            }
            System.out.print(total + (i + 1 < n ? " " : "\n"));
        }

        in.close();
        out.close();
    }

    public static int search(int gcd, int left, int[][] sparse) {
        int l = left;
        int r = sparse[0].length - 1;
        while (l < r) {
            int mid = (l + r) / 2;

        }
        return 0;
    }

    public static int rangeGCD(int l, int r, int[][] sparse) {
        int interval = Integer.highestOneBit(r - l + 1);
        int width = Integer.numberOfTrailingZeros(interval) + 1;
        return gcd(sparse[width][l], sparse[width][r - interval + 1]);
    }

    public static int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
}