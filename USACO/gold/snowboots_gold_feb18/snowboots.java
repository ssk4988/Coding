/*
ID: ssk49881
LANG: JAVA
TASK: snowboots
*/

import java.io.*;
import java.util.*;

public class snowboots {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("snowboots.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snowboots.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numSteps = Integer.parseInt(tokenizer.nextToken());
        int numBoots = Integer.parseInt(tokenizer.nextToken());
        Step[] steps = new Step[numSteps];
        Boot[] boots = new Boot[numBoots];
        tokenizer = new StringTokenizer(in.readLine());
        TreeSet<Step> set = new TreeSet<>();
        for (int i = 0; i < numSteps; i++) {
            steps[i] = new Step(i, Integer.parseInt(tokenizer.nextToken()));
            set.add(steps[i]);
        }
        steps[0].right = steps[1];
        steps[numSteps - 1].left = steps[numSteps - 2];
        for (int i = 1; i < numSteps - 1; i++) {
            steps[i].right = steps[i + 1];
            steps[i].left = steps[i - 1];
        }
        for (int i = 0; i < numBoots; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int maxDepth = Integer.parseInt(tokenizer.nextToken());
            int maxStep = Integer.parseInt(tokenizer.nextToken());
            boots[i] = new Boot(maxDepth, maxStep, i);
        }
        Arrays.sort(boots);
        int maxSteps = 1;
        boolean[] works = new boolean[numBoots];
        for (int i = 0; i < numBoots; i++) {
            while (set.size() > 0 && set.last().depth > boots[i].depth) {
                Step st = set.last();
                int s = st.right.index - st.left.index;
                if (s > maxSteps) {
                    maxSteps = s;
                }
                st.right.left = st.left;
                st.left.right = st.right;
                set.remove(st);
            }
            works[boots[i].index] = maxSteps <= boots[i].steps;
        }
        for (int i = 0; i < numBoots; i++) {
            out.println(works[i] ? 1 : 0);
        }

        in.close();
        out.close();
    }

    public static class Step implements Comparable<Step> {
        int index;
        int depth;
        Step right;
        Step left;

        public Step(int index, int depth) {
            this.index = index;
            this.depth = depth;
        }

        @Override
        public int compareTo(snowboots.Step o) {
            if (depth == o.depth)
                return index - o.index;
            return depth - o.depth;
        }
    }

    public static class Boot implements Comparable<Boot> {
        int depth;
        int steps;
        int index;

        public Boot(int depth, int steps, int index) {
            this.depth = depth;
            this.steps = steps;
            this.index = index;
        }

        @Override
        public int compareTo(snowboots.Boot o) {
            if (o.depth == depth) {
                return o.steps - steps;
            }
            return o.depth - depth;
        }
    }
}