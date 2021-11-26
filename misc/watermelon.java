/*
ID: ssk49881
LANG: JAVA
TASK: watermelon
*/

import java.io.*;
import java.util.*;

public class watermelon {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        if (n != 2 && n % 2 == 0) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }

        in.close();
        out.close();
    }
}