import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numLines = Integer.parseInt(tokenizer.nextToken());
        int numErrors = Integer.parseInt(tokenizer.nextToken());
        boolean[] error = new boolean[numLines];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numErrors; i++) {
            error[Integer.parseInt(tokenizer.nextToken()) - 1] = true;
        }
        ArrayList<range> good = new ArrayList<>();
        ArrayList<range> bad = new ArrayList<>();
        for (int i = 0; i < numLines; i++) {
            boolean type = error[i];
            int first = i;
            int second = first;
            while (second + 1 < numLines && error[second + 1] == type) {
                second++;
            }
            range r = new range(first, second, type);
            if (type) {
                bad.add(r);
            } else {
                good.add(r);
            }
            i = second;
        }
        Collections.sort(good);
        Collections.sort(bad);
        System.out.print("Errors: ");
        for (int i = 0; i < bad.size(); i++) {
            if (i + 1 == bad.size()) {
                System.out.print(" and ");
            }
            System.out.print(bad.get(i));
            if (i + 2 < bad.size()) {
                System.out.print(", ");
            }

        }
        System.out.println();
        System.out.print("Correct: ");
        for (int i = 0; i < good.size(); i++) {
            if (i + 1 == good.size()) {
                System.out.print(" and ");
            }
            System.out.print(good.get(i));
            if (i + 2 < good.size()) {
                System.out.print(", ");
            }

        }
        System.out.println();

        in.close();
        out.close();
    }

    public static class range implements Comparable<range> {
        int first;
        int second;
        boolean type;

        public range(int first, int second, boolean type) {
            this.first = first;
            this.second = second;
            this.type = type;
        }

        @Override
        public int compareTo(g.range o) {
            return this.first - o.first;
        }

        @Override
        public String toString() {
            if (first == second) {
                return (first + 1) + "";
            }
            return (first + 1) + "-" + (second + 1);
        }
    }
}