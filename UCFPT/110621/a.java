/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int needed = Integer.parseInt(tokenizer.nextToken());
        double[] distances = new double[n];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            double x = Double.parseDouble(tokenizer.nextToken());
            double y = Double.parseDouble(tokenizer.nextToken());
            double z = Double.parseDouble(tokenizer.nextToken());
            double distance = Math.sqrt(x * x + y * y + z * z);
            distances[i] = distance;
        }
        Arrays.sort(distances);
        System.out.println(distances[needed - 1]);

        in.close();
        out.close();
    }
}