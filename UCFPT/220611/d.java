import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] row = new int[200059];
        int[] col = new int[200059];
        int rowans = 0;
        int colans = 0;
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken()) + 5;
            int y = Integer.parseInt(tokenizer.nextToken()) + 5;
            col[x]++;
            row[y]++;
            if (col[x] == 1)
                colans += 2;
            if (row[y] == 1)
                rowans += 2;

            if (col[x - 1] < col[x])
                colans++;
            else
                colans--;

            if (col[x + 1] < col[x])
                colans++;
            else
                colans--;

            if (row[y - 1] < row[y])
                rowans++;
            else
                rowans--;

            if (row[y + 1] < row[y])
                rowans++;
            else
                rowans--;

            b.append(colans + " " + rowans + "\n");
        }
        System.out.print(b);
        in.close();
    }
}