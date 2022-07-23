import java.io.*;
import java.util.*;

public class snow {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int casenum = Integer.parseInt(in.readLine());
        for (int i = 0; i < casenum; i++) {
            int numSnow = Integer.parseInt(in.readLine());
            man[] men = new man[numSnow];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < numSnow; j++) {
                men[j] = new man();
                men[j].index = j;
                men[j].height = Integer.parseInt(tokenizer.nextToken());
            }
            for (int j = 0; j < numSnow; j++) {
                men[j].left = men[(numSnow * 2 + j - 1) % numSnow];
                men[j].right = men[(numSnow * 2 + j + 1) % numSnow];
            }
            Arrays.sort(men);
            int point = 0;
            String dir = in.readLine();
            int moves;
            int numLeft = numSnow;
            for (moves = 0; moves < numSnow; moves++) {
                // System.out.println("Left: " + numLeft + " " + moves + " " +
                // men[point].toString());
                numLeft -= men[point].height;
                if (numLeft <= 0)
                    break;
                men[point].destroy(dir.charAt(moves) == 'L' ? -1 : 1);
                while (men[++point].destroyed) {
                    // System.out.println("n index: " + point + " " + men.length);
                }
            }
            if (moves == numSnow)
                moves--;
            System.out.println((moves + 1));
        }

        in.close();
        out.close();
    }

    public static class man implements Comparable<man> {
        int index;
        int height = 0;
        man right;
        man left;
        boolean destroyed = false;

        @Override
        public int compareTo(snow.man o) {
            if (this.height == o.height) {
                return this.index - o.index;
            }
            return o.height - this.height;
        }

        @Override
        public String toString() {
            return this.index + " " + this.height + " " + this.left.index + " " + this.right.index + " " + destroyed;
        }

        public void destroy(int dir) { // -1 left 1 right
            this.destroyed = true;
            man l = this;
            man r = this;
            if (dir == -1) {
                for (int i = 0; i < height; i++) {
                    l = l.left;
                    if (i < height - 1) {
                        l.destroyed = true;
                    }
                }
                r = r.right;
            } else {
                for (int i = 0; i < height; i++) {
                    r = r.right;
                    if (i < height - 1) {
                        r.destroyed = true;
                    }
                }
                l = l.left;
            }
            l.right = r;
            r.left = l;
        }
    }
}