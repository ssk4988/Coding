/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class salaryqueries {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int[] inputArr = new int[size + 1];
        tokenizer = new StringTokenizer(in.readLine());
        Set<Integer> nums = new HashSet<>();
        for (int i = 0; i < size; i++) {
            inputArr[i + 1] = Integer.parseInt(tokenizer.nextToken());
            nums.add(inputArr[i + 1]);
        }
        int[] inputQueries = new int[numQueries*3];
        int ind = 0;
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int t = tokenizer.nextToken().charAt(0) == '!' ? 0 : 1;
            int i1 = Integer.parseInt(tokenizer.nextToken());
            int i2 = Integer.parseInt(tokenizer.nextToken());
            inputQueries[ind++] = t;
            inputQueries[ind++] = i1;
            inputQueries[ind++] = i2;
            nums.add(i2);
            if (t == 1) {
                nums.add(i1);
            }
        }
        int[] lnum = new int[nums.size()];
        Map<Integer, Integer> compress = new HashMap<>();
        ind = 0;
        for(int i : nums){
            lnum[ind++] = i;
        } 
        Arrays.sort(lnum);
        for (int i = 0; i < lnum.length; i++) {
            compress.put(lnum[i], i + 1);
            // System.out.println("Mapping: " + lnum.get(i) + " to " +
            // compress.get(lnum.get(i)));
        }
        long[] tree = new long[lnum.length + 1];
        for (int i = 1; i < inputArr.length; i++) {
            inputArr[i] = compress.get(inputArr[i]);
            update(inputArr[i], 1, tree);
        }
        for (int i = 0; i < inputQueries.length; i += 3) {
            int t = inputQueries[i];
            int i1 = inputQueries[i + 1];
            int i2 = inputQueries[i + 2];
            if (t == 0) {
                update(inputArr[i1], -1, tree);
                inputArr[i1] = compress.get(i2);
                update(inputArr[i1], 1, tree);
            } else {
                long answer = sum(compress.get(i2), tree) - sum(compress.get(i1) - 1, tree);
                b.append(answer + "\n");
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static long sum(int index, long[] tree) {
        long sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    public static void update(int index, long change, long[] tree) {
        int size = tree.length - 1;
        while (index <= size) {
            tree[index] += change;
            index += index & -index;
        }
    }
}