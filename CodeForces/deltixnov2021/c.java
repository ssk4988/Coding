import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int size = Integer.parseInt(tokenizer.nextToken());
            int e = Integer.parseInt(tokenizer.nextToken());
            int[][] arr = new int[e][size / e + 1];
            boolean[][] prime = new boolean[e][size / e + 1];
            boolean[][] one = new boolean[e][size / e + 1];
            int[][] left1 = new int[e][size / e + 1];
            int[][] right1 = new int[e][size / e + 1];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < size; i++) {
                arr[i % e][i / e] = Integer.parseInt(tokenizer.nextToken());
                prime[i % e][i / e] = isPrime(arr[i % e][i / e]);
                one[i % e][i / e] = arr[i % e][i / e] == 1;
            }
            for (int i = 0; i < e; i++) {
                for (int j = 1; j < arr[i].length; j++) {
                    left1[i][j] = one[i][j - 1] ? left1[i][j - 1] + 1 : 0;
                }
            }
            for (int i = 0; i < arr.length; i++) {
                for (int j = arr[i].length - 2; j >= 0; j--) {
                    right1[i][j] = one[i][j + 1] ? right1[i][j + 1] + 1 : 0;
                }
            }
            long answer = 0;
            for (int i = 0; i < arr.length; i++) {
                for (int j = 0; j < arr[i].length; j++) {
                    if (prime[i][j] && 1 + right1[i][j] + left1[i][j] >= 2) {
                        answer += (long) (right1[i][j] + 1) * (left1[i][j] + 1) - 1;
                    }
                }
            }

            b.append(answer + "\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static boolean isPrime(int k) {
        if (k < 2)
            return false;
        if (k <= 3)
            return true;
        if (k % 2 == 0)
            return false;
        for (int i = 3; i * i <= k; i += 2) {
            if (k % i == 0)
                return false;
        }
        return true;
    }
}