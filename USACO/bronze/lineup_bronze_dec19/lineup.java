
import java.io.*;
import java.util.*;

public class lineup {
    public static ArrayList<String> possible = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("lineup.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lineup.out")));
        String[] cowNames = { "Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue" };
        Arrays.sort(cowNames);
        int numConstraints = Integer.parseInt(in.readLine());
        int[][] constraints = new int[numConstraints][2];
        for (int i = 0; i < numConstraints; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String x = tokenizer.nextToken();
            for (int j = 0; j < cowNames.length; j++) {
                if (cowNames[j].equals(x)) {
                    constraints[i][0] = j;
                    break;
                }
            }
            tokenizer.nextToken();
            tokenizer.nextToken();
            tokenizer.nextToken();
            tokenizer.nextToken();
            x = tokenizer.nextToken();
            for (int j = 0; j < cowNames.length; j++) {
                if (cowNames[j].equals(x)) {
                    constraints[i][1] = j;
                    break;
                }
            }
            System.out.println(constraints[i][0] + " " + constraints[i][1]);
        }
        solve("", "01234567");
        iterate: for (String solution : possible) {
            for (int i = 0; i < numConstraints; i++) {
                if (Math.abs(solution.indexOf(Integer.toString(constraints[i][0]))
                        - solution.indexOf(Integer.toString(constraints[i][1]))) != 1) {
                    continue iterate;
                }
            }
            for (int i = 0; i < solution.length(); i++) {
                out.println(cowNames[Integer.parseInt(solution.substring(i, i + 1))]);
            }
            break;
        }
        in.close();
        out.close();
    }

    public static String solve(String prefix, String str) {
        int len = str.length();
        if (len == 0) {
            possible.add(prefix);
        }
        for (int i = 0; i < len; i++) {
            solve(prefix + str.substring(i, i + 1), str.substring(0, i) + str.substring(i + 1, str.length()));
        }
        return "";
    }
}