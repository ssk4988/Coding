import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int size = Integer.parseInt(in.readLine());
            int[] arr = new int[size];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int min = Integer.MAX_VALUE;
            for (int i = 0; i < size; i++) {
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                min = Math.min(arr[i], min);
            }
            int size2 = size / 2;
            int answer = 0;
            for (int i = 0; i < size && answer < size2; i++) {
                if(arr[i] == min) continue;
                b.append(arr[i] + " " + min + "\n");
                answer++;
            }
        }
        System.out.print(b);
        in.close();
    }
}