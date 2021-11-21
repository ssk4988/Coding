/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class baseconvert {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String num = in.readLine();
        int base1 = Integer.parseInt(in.readLine());
        int base2 = Integer.parseInt(in.readLine());
        System.out.println(Integer.toString(Integer.parseInt(num, base1), base2));
        in.close();
        out.close();
    }
}