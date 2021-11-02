/*
ID: ssk49881
LANG: JAVA
TASK: helpcross
*/

import java.io.*;
import java.util.*;

public class helpcross {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("helpcross.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("helpcross.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numChickens = Integer.parseInt(tokenizer.nextToken());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int[] chickens = new int[numChickens];
        ArrayList<Tuple> cows = new ArrayList<>();
        for (int i = 0; i < numChickens; i++) {
            chickens[i] = Integer.parseInt(in.readLine());
        }
        for (int i = 0; i < numCows; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken());
            int second = Integer.parseInt(tokenizer.nextToken());
            cows.add(new Tuple(first, second));
        }
        Arrays.sort(chickens);
        Collections.sort(cows, new CompTuple());
        int numMatches = 0;
        for (int c : chickens) {
            int earliesttime = Integer.MAX_VALUE;
            int index = -1;
            for (int i = 0; i < cows.size(); i++) {
                Tuple cow = cows.get(i);
                if (cow.second < c) {
                    continue;
                }
                if (cow.first > c) {
                    break;
                }
                if (cow.second < earliesttime) {
                    earliesttime = cow.second;
                    index = i;
                }

            }
            if (index != -1) {
                numMatches++;
                cows.remove(index);
            }
        }
        out.println(numMatches);

        in.close();
        out.close();
    }

    public static class Tuple {
        int first;
        int second;

        public Tuple(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    public static class CompTuple implements Comparator<Tuple> {
        @Override
        public int compare(helpcross.Tuple o1, helpcross.Tuple o2) {
            return o1.first == o2.first ? o1.second - o2.second : o1.first - o2.first;
        }
    }
}