/*
ID: ssk49881
LANG: JAVA
TASK: snowboots
*/

import java.io.*;
import java.util.*;

public class snowboots {
    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("12.in"));
        BufferedReader inOut = new BufferedReader(new FileReader("12.out"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new
        // FileWriter("snowboots.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        ArrayList<Boot> boots = new ArrayList<>();
        ArrayList<Boot> bootsDepth = new ArrayList<>();
        int numSteps = Integer.parseInt(tokenizer.nextToken());
        int numBoots = Integer.parseInt(tokenizer.nextToken());
        ArrayList<Step> steps = new ArrayList<>();
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numSteps; i++) {
            steps.add(new Step(i, Integer.parseInt(tokenizer.nextToken())));
        }
        steps.get(0).right = steps.get(1);
        steps.get(numSteps - 1).left = steps.get(numSteps - 2);
        for(int i = 1; i < numSteps - 1; i++){
            steps.get(i).right = steps.get(i + 1);
            steps.get(i).left = steps.get(i - 1);
        }
        int numRight = 0;
        for (int i = 0; i < numBoots; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int maxDepth = Integer.parseInt(tokenizer.nextToken());
            int maxStep = Integer.parseInt(tokenizer.nextToken());
            boots.add(new Boot(maxDepth, maxStep, i));
            bootsDepth.add(boots.get(i));
        }
        steps.sort(new CompStep());
        bootsDepth.sort(new CompDepth());
        int maxSteps = 1;
        for (int i = 0; i < numBoots; i++) {
            Boot boot = bootsDepth.get(i);
            while(steps.size() > 0 && steps.get(0).depth > boot.depth){
                Step st = steps.get(0);
                int s = st.right.index - st.left.index;
                if (s > maxSteps) {
                    maxSteps = s;
                }
                st.right.left = st.left;
                st.left.right = st.right;
                steps.remove(0);
            }
            boot.works = maxSteps <= boot.steps ? 1 : 0;
        }
        for (int i = 0; i < numBoots; i++) {
            if (Integer.parseInt(inOut.readLine()) == boots.get(i).works) {
                numRight++;
            }
        }
        System.out.println(numRight + " " + numBoots + " " + (System.currentTimeMillis() - start));

        in.close();
        // out.close();
    }

    public static class Step {
        int index;
        int depth;
        Step right;
        Step left;

        public Step(int index, int depth) {
            this.index = index;
            this.depth = depth;
        }
    }

    public static class Boot {
        int depth;
        int steps;
        int index;
        int works;

        public Boot(int depth, int steps, int index) {
            this.depth = depth;
            this.steps = steps;
            this.index = index;
        }
    }

    public static class CompStep implements Comparator<Step>{
        @Override
        public int compare(snowboots.Step o1, snowboots.Step o2) {
            return o2.depth - o1.depth;
        }
    }

    public static class CompDepth implements Comparator<Boot> {
        @Override
        public int compare(snowboots.Boot o1, snowboots.Boot o2) {
            if (o2.depth == o1.depth) {
                return o2.steps - o1.steps;
            }
            return o2.depth - o1.depth;
        }
    }

    public static class CompIndex implements Comparator<Boot> {
        @Override
        public int compare(snowboots.Boot o1, snowboots.Boot o2) {
            return o1.index - o2.index;
        }
    }
}