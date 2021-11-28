import java.io.*;
import java.util.*;

public class jenny {
    public static ArrayList<Integer>[] jennyNums = new ArrayList[10];

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        for (int i = 0; i < jennyNums.length; i++) {
            jennyNums[i] = new ArrayList<>();
        }
        boolean[] arr = new boolean[10];
        generate(0, 0, arr);
        for (int i = 0; i < jennyNums.length; i++) {
            //System.out.println(jennyNums[i].size());
            Collections.sort(jennyNums[i]);
        }
        //System.out.println(jennyNums[1]);
        //System.out.println(jennyNums[2]);
        //System.out.println(jennyNums[3]);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int d = Integer.parseInt(tokenizer.nextToken());
            int i = Integer.parseInt(tokenizer.nextToken());
            if (d > 9 || i > jennyNums[d].size()) {
                System.out.println("Brice doesn't stand a chance!");
            } else {
                System.out.println(jennyNums[d].get(i - 1));
            }
        }

        in.close();
        out.close();
    }

    public static boolean qualifies(int num) {
        if (num < 2)
            return false;
        if (num == 2)
            return true;
        if (num % 2 == 0)
            return false;
        for (int i = 3; i * i <= num + 2; i += 2) {
            if (num % i == 0 || (num + 2) % i == 0)
                return false;
        }
        return true;
    }

    public static void generate(int index, int curr, boolean[] using) {
        if (index > 9)
            return;
        if (qualifies(curr) && Math.log10(curr) >= index-1) {
            jennyNums[index].add(curr);
        }

        for (int i = 0; i < using.length; i++) {
            if (using[i])
                continue;
            using[i] = true;
            generate(index + 1, curr * 10 + i, using);
            using[i] = false;
        }
    }
}