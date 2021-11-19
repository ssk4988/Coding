/*
ID: ssk49881
LANG: JAVA
TASK: pi
*/

import java.io.*;
import java.util.*;

public class pi {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        System.out.printf("%."+n+"f", Math.PI);

        in.close();
        out.close();
    }
}