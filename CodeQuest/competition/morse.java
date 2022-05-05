import java.io.*;
import java.util.*;

public class morse {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            String[] code = new String[26];
            for (int i = 0; i < 26; i++) {
                String s = in.readLine();
                int v = s.charAt(0) - 'A';
                s = s.substring(2);
                code[v] = s;
            }
            String input = in.readLine();
            for (int i = 0; i < input.length(); i++) {
                if (input.charAt(i) == ' ') {
                    for (int j = 0; j < 7; j++) {
                        b.append(' ');
                    }

                } else {
                    b.append(code[input.charAt(i) - 'A']);
                    if ((i + 1 < input.length() && input.charAt(i) != ' ')) {
                        for (int j = 0; j < 3; j++) {
                            b.append(' ');
                        }
                    }
                }

            }
            b.append("\n");
            input = in.readLine();
            int index = 0;
            while (index < input.length()) {
                StringBuilder c = new StringBuilder();
                c.append(input.charAt(index));
                boolean end = true;
                while (index < input.length()) {
                    for (int j = 1; j < 8 && (index + j) < input.length(); j++) {
                        if (input.charAt(index + j) != ' ') {
                            end = false;
                            break;
                        }
                    }
                    if (end) {
                        break;
                    }
                }
                String c1 = c.toString();
                for (int i = 0; i < code.length; i++) {
                    if (code[i].equals(c1)) {
                        b.append((char) ('A' + i));
                    }
                }
                index++;
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}