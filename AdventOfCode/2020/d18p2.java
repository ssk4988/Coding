import java.io.*;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;

public class d18p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d18p1.in"));
        long totalVals = 0;
        String line;
        while ((line = in.readLine()) != null) {
            long val = solve(line);
            //System.out.println(val);
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
        // System.out.println(s);
        return removeParen(l);
    }

    public static long solve(String input) {
        if (input.indexOf("(") != -1) {
            input = removeParen(input);
        }
        String[] str = input.split(" ");
        ArrayList<Long> vals = new ArrayList<>();
        ArrayList<Integer> ops = new ArrayList<>();
        for (int i = 0; i < str.length; i++) {
            if (i % 2 == 0)
                vals.add(Long.parseLong(str[i]));
            else {
                if (str[i].charAt(0) == '+')
                    ops.add(0);
                else if (str[i].charAt(0) == '*')
                    ops.add(1);
            }
        }
        long total = 1;
        // System.out.println(input);
        for (int i = 0; i < ops.size(); i++) {
            if (ops.get(i) == 0) {
                vals.set(i, vals.get(i) + vals.get(i + 1));
                vals.remove(i + 1);
                ops.remove(i);
                i--;
            }
        }
        for (int i = 0; i < vals.size(); i++) {
            total *= vals.get(i);
        }
        //System.out.println(input + " " + total);
        return total;
    }
}
