import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for(int i = 0; i < n; i++){
            int length = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            long[] arr = new long[length];
            long mult = 1;
            long answer = 0;
            int maxIndex = 0;
            for(int j =0; j < length; j++){
                arr[j] = Long.parseLong(tokenizer.nextToken());
                long mult2 = arr[j] & -arr[j];
                arr[j] /= mult2;
                mult *= mult2;
                if(arr[maxIndex] < arr[j]) maxIndex = j;
            }
            for(int j = 0; j < length; j++){
                if(j == maxIndex) answer += arr[j] * mult;
                else answer += arr[j];
            }
            System.out.println(answer);
        }
        in.close();
        out.close();
    }
}