import java.io.*;
import java.util.*;

public class word {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<Integer> lengths = new ArrayList<>();
            int[] freq = new int[100];
            int max = 0;
            int min = 100;
            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                while (tokenizer.hasMoreTokens()) {
                    String s = tokenizer.nextToken();
                    int len = 0;
                    for (int j = 0; j < s.length(); j++) {
                        char c = s.charAt(j);
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                            len++;
                        }
                    }

                    lengths.add(len);
                    freq[len]++;
                    if (len > max)
                        max = len;
                    if (len < min)
                        min = len;
                }
            }
            Collections.sort(lengths);
            double average = 0;
            for (int i = 0; i < lengths.size(); i++) {
                average += lengths.get(i);
            }
            average /= lengths.size();
            double median = 0;
            if (lengths.size() % 2 == 0) {
                median += lengths.get(lengths.size() / 2);
                median += lengths.get(lengths.size() / 2 - 1);
                median /= 2;
            } else {
                median = lengths.get(lengths.size() / 2);
            }
            ArrayList<Integer> modes = new ArrayList<>();
            int mode = 1;
            for (int i = 0; i < freq.length; i++) {
                if (freq[i] > mode) {
                    mode = freq[i];
                    modes = new ArrayList<>();
                    modes.add(i);
                } else if (freq[i] == mode) {
                    modes.add(i);
                }
            }
            Collections.sort(modes);
            b.append(String.format("Average: %.1f\n", average));
            b.append(String.format("Median: %.1f\n", median));
            b.append("Modes: ");
            for (int i = 0; i < modes.size(); i++) {
                b.append(modes.get(i) + (i + 1 < modes.size() ? "," : "\n"));
            }
            b.append(String.format("Range: %d\n", max - min));
            for (int i = min; i <= max; i++) {
                b.append(String.format("%2d|", i));
                for (int j = 0; j < freq[i]; j++) {
                    b.append("x");
                }
                b.append("\n");
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}