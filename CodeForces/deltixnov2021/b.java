import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        String s = in.readLine();
        int[] arr = new int[size];
        int currentabc = 0;
        for (int i = 0; i < size; i++) {
            arr[i] = s.charAt(i) - 'a';
            if (i >= 2 && arr[i] == 2 && arr[i - 1] == 1 && arr[i - 2] == 0)
                currentabc++;
        }
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int index = Integer.parseInt(tokenizer.nextToken()) - 1;
            int rep = tokenizer.nextToken().charAt(0) - 'a';
            if (rep != arr[index]) {
                if (index >= 2 && rep == 2 && arr[index - 1] == 1 && arr[index - 2] == 0)
                    currentabc++;
                if (index >= 2 && arr[index] == 2 && arr[index - 1] == 1 && arr[index - 2] == 0)
                    currentabc--;
                if (index >= 1 && index < size - 1 && rep == 1 && arr[index + 1] == 2 && arr[index - 1] == 0)
                    currentabc++;
                if (index >= 1 && index < size - 1 && arr[index] == 1 && arr[index + 1] == 2 && arr[index - 1] == 0)
                    currentabc--;
                if (index < size - 2 && rep == 0 && arr[index + 1] == 1 && arr[index + 2] == 2)
                    currentabc++;
                if (index < size - 2 && arr[index] == 0 && arr[index + 1] == 1 && arr[index + 2] == 2)
                    currentabc--;
            }
            arr[index] = rep;
            System.out.println(currentabc);
        }
        in.close();
        out.close();
    }
}