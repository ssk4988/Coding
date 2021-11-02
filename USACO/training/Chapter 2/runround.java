/*
ID: ssk49881
LANG: JAVA
TASK: runround
*/

import java.io.*;
import java.util.*;

public class runround {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("runround.in"));
        PrintWriter out = new PrintWriter(new File("runround.out"));
        int m = Integer.parseInt(in.nextLine());

        int i = m + 1;
        while (!(hasRunaroundFormat(i) && isRunaround(i))) {
            i++;
        }
        out.println(i);

        in.close();
        out.close();
    }

    public static boolean hasRunaroundFormat(int num) {
        String digits = "";
        String numstr = Integer.toString(num);
        for (int i = 0; i < numstr.length(); i++) {
            if (numstr.charAt(i) == '0') {
                return false;
            }
            if (digits.contains(String.valueOf(numstr.charAt(i)))) {
                return false;
            }
            digits += numstr.charAt(i);
        }
        return true;
    }

    public static boolean isRunaround(int num) {
        String numstr = Integer.toString(num);
        int sum = 0;
        for (char chr : numstr.toCharArray()) {
            sum += Integer.parseInt(String.valueOf(chr));
        }
        if (sum % numstr.length() != 0) {
            return false;
        }
        String digits = "";
        int index = 0;
        char chr = numstr.charAt(index);
        while (!digits.contains(String.valueOf(chr))) {
            digits += chr;
            index = (index + Integer.parseInt(String.valueOf(chr))) % numstr.length();
            chr = numstr.charAt(index);
        }
        if (digits.length() == numstr.length() && index == 0) {
            return true;
        }
        return false;
    }
}