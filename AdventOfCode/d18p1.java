import java.io.*;
import java.util.*;

public class d18p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d18p1.in"));
        long totalVals = 0;
        String line;
        while ((line = in.readLine()) != null) {
            long val = solve(line);
            System.out.println(val);
            totalVals += val;
        }
        System.out.println(totalVals);
        in.close();
    }

    public static String removeParen(String input) {
        if (input.indexOf("(") == -1) {
            return input;
        }
        int start = input.indexOf("(");
        int end = -1;
        int numParen = 0;
        for (int i = input.indexOf("("); i < input.length(); i++) {
            if (input.charAt(i) == '(') {
                numParen++;
            }
            if (input.charAt(i) == ')') {
                numParen--;
            }
            if (numParen == 0) {
                end = i;
                break;
            }
        }
        String s = input.substring(start + 1, end);
        String l = input.replace(input.substring(start, end + 1), Long.toString(solve(s)));
        //System.out.println(s);
        return removeParen(l);
    }

    public static long solve(String input) {
        if (input.indexOf("(") != -1) {
            input = removeParen(input);
        }
        String[] str = input.split(" ");
        int[] vals = new int[(str.length + 1) / 2];
        int[] ops = new int[str.length / 2];
        long total = 0;
        //System.out.println(input);
        for (int i = 0; i < str.length; i += 2) {
            // int
            long val = 0;
            int op = -1; // 0 + 1 - 2 *
            if (i == 0)
                op = 0;
            else {
                if (str[i - 1].charAt(0) == '+')
                    op = 0;
                else if (str[i - 1].charAt(0) == '*')
                    op = 1;
            }
            val = Long.parseLong(str[i]);
            if (op == 0)
                total += val;
            else if (op == 1)
                total *= val;
        }
        return total;
    }
}
