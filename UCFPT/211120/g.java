/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line = in.readLine();
        while (!line.equals("0")) {

            StringTokenizer tokenizer = new StringTokenizer(line);
            int period = Integer.parseInt(tokenizer.nextToken());
            char c = 'A';
            int[] heights = new int[period];
            String[] catches = new String[20];
            Arrays.fill(catches, "1");
            boolean crash = false;
            for (int i = 0; i < period; i++) {
                heights[i] = Integer.parseInt(tokenizer.nextToken());
            }

            for (int i = 0; i < catches.length; i++) {
                if (catches[i].equals("1")) {
                    catches[i] = Character.toString(c);
                    c = (char) (c + 1);
                }
                if (i + heights[i % period] < catches.length
                        && !catches[i + heights[i % period]].equals("1"))
                    crash = true;
                if (i + heights[i % period] < catches.length)
                    catches[i + heights[i % period]] = catches[i];
            }
            if (crash) {
                System.out.println("CRASH");
            } else {
                for (String s : catches) {
                    System.out.print(s);
                }
                System.out.println();
            }
            line = in.readLine();
        }

        in.close();
        out.close();
    }
}