/*
ID: ssk49881
LANG: JAVA
TASK: barn1
*/

import java.io.*;
import java.util.*;

public class barn1 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("barn1.in"));
        PrintWriter out = new PrintWriter(new File("barn1.out"));
        String phrase = in.nextLine();
        int m = Integer.parseInt(phrase.split(" ")[0]);
        int s = Integer.parseInt(phrase.split(" ")[1]);
        int c = Integer.parseInt(phrase.split(" ")[2]);
        boolean[] stalls = new boolean[s + 1];
        ArrayList<Gap> actualGaps = new ArrayList<>();
        ArrayList<Gap> boardGaps = new ArrayList<>();
        Arrays.fill(stalls, false);
        int firststall = 1000;
        int laststall = 0;
        for (int i = 0; i < c; i++) {
            int stall = Integer.parseInt(in.nextLine());
            if (stall < firststall) {
                firststall = stall;
            }
            if (stall > laststall) {
                laststall = stall;
            }
            stalls[stall] = true;
        }
        actualGaps.add(new Gap(0, firststall));
        actualGaps.add(new Gap(laststall + 1, s + 2));
        boardGaps.add(new Gap(0, firststall));
        boardGaps.add(new Gap(laststall + 1, s + 2));
        int start = -1;
        int end = -1;
        for (int i = firststall; i < laststall + 1; i++) {
            if (stalls[i]) {
                end = i;
                if (start != -1) {
                    if (start != i) {
                        actualGaps.add(new Gap(start, end));
                    }
                    start = i + 1;
                }
            } else {
                if (start == -1) {
                    start = i;
                }
                end = i + 1;
            }
        }
        Collections.sort(actualGaps);
        for (int i = 0; boardGaps.size() < actualGaps.size() && boardGaps.size() - 1 < m; i++) {
            Gap gap = actualGaps.get(i);
            if (gap.start != 0 && gap.start != laststall + 1) {
                boardGaps.add(gap);
            }
        }
        out.println(s - (getSum(boardGaps) - 2));

        in.close();
        out.close();
    }

    public static int getSum(ArrayList<Gap> gaps) {
        int sum = 0;
        for (Gap gap : gaps) {
            sum += gap.size;
        }
        return sum;
    }
}

class Gap implements Comparable<Gap> {
    public int start;
    public int end;
    public int size;

    public Gap(int start, int end) {
        this.start = start;
        this.end = end;
        this.size = end - start;
    }

    @Override
    public int compareTo(Gap o) {
        return o.size - this.size;
    }
}