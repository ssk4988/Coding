import java.io.*;
import java.util.*;

public class abc {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long[] nums = new long[7];
        for (int i = 0; i < nums.length; i++) {
            nums[i] = Long.parseLong(tokenizer.nextToken());
        }
        Arrays.sort(nums);
        long a = nums[0];
        long b = nums[1];
        long c = nums[6] - a - b;
        System.out.println(a + " " + b + " " + c);

        in.close();
        // out.close();
    }
}