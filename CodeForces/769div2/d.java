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
                    sparse[i][j] = gcd(sparse[i][j], sparse[i - 1][j + (interval>>1)]);
                }
            }
        }
        ArrayList<range> ranges = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int index = search(i, sparse);
            if (rangeGCD(i, index, sparse) == (index - i + 1)) {
                ranges.add(new range(i, index));
            }
        }
        Collections.sort(ranges);
        ArrayList<Integer> adds = new ArrayList<>();
        for (int i = 0; i < ranges.size(); i++) {
            range r = ranges.get(i);
            int i1 = Collections.binarySearch(adds, r.first);
            int i2 = Collections.binarySearch(adds, r.second);
            int i12 = i1 < 0 ? -i1 - 1 : i1;
            int i22 = i2 < 0 ? -i2 - 1 : i2;

            if (i1 >= 0 || i2 >= 0) {
                // obv covered
            } else if (i12 != i22) {
                // on diff sides of one so chillin
            } else {
                adds.add(r.second);
            }
        }
        int[] answer = new int[n];
        for (int i : adds) {
            answer[i]++;
        }
        for (int i = 0; i + 1 < n; i++) {
            answer[i + 1] += answer[i];
        }
        for (int i = 0; i < n; i++) {
            System.out.print(answer[i] + " ");
        }
        System.out.println();

        in.close();
        out.close();
    }

    public static class range implements Comparable<range> {
        int first;
        int second;

        public range(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int compareTo(d.range o) {
            if (this.second == o.second)
                return this.first - o.first;
            return this.second - o.second;
        }
    }

    public static int search(int left, int[][] sparse) {
        int l = left;
        int r = sparse[0].length - 1;
        while (l < r) {
            int mid = l + (r - l + 1) / 2;
            int gcd = rangeGCD(left, mid, sparse);
            if (gcd >= (mid - left + 1)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }

    public static int rangeGCD(int l, int r, int[][] sparse) {
        int interval = Integer.highestOneBit(r - l + 1);
        int width = Integer.numberOfTrailingZeros(interval);
        return gcd(sparse[width][l], sparse[width][r - interval + 1]);
    }

    public static int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
}