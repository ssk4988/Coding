/*
ID: ssk49881
LANG: JAVA
TASK: zerosum
*/

import java.io.*;
import java.util.*;

public class zerosum {
    public static ArrayList<int[]> solutions = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("zerosum.in"));
        PrintWriter out = new PrintWriter(new File("zerosum.out"));
        int n = Integer.parseInt(in.nextLine());
        ArrayList<Integer> numbers = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            numbers.add(i + 1);
        }
        ArrayList<Integer> operations = new ArrayList<>(); // 1 - ' ' 2 - + 3 - -
        for (int i = 0; i < n - 1; i++) {
            operations.add(1);
        }
        System.out.println(operations.size());

        expand(0, operations, numbers, n);
        System.out.println(solutions.size());
        for (int[] solution : solutions) {
            for (int i = 0; i < solution.length; i++) {
                out.print(numbers.get(i));
                if (solution[i] == 1) {
                    out.print(" ");
                }
                if (solution[i] == 2) {
                    out.print("+");
                }
                if (solution[i] == 3) {
                    out.print("-");
                }
            }
            out.println(numbers.get(numbers.size() - 1));
        }
        in.close();
        out.close();
    }

    public static void expand(int index, ArrayList<Integer> operations, ArrayList<Integer> numbers, int n) {
        if (index == n - 1) {
            int sum = sumSequence(numbers, operations);
            if (sum == 0) {
                int[] oparray = new int[n - 1];
                for (int i = 0; i < operations.size(); i++) {
                    oparray[i] = operations.get(i);
                    System.out.print(oparray[i] + " ");
                }
                solutions.add(oparray);
                System.out.println(sum);
            }
            return;
        }

        for (int i = 1; i <= 3; i++) {
            operations.set(index, i);

            expand(index + 1, operations, numbers, n);
        }
    }

    public static int sumSequence(ArrayList<Integer> numbers, ArrayList<Integer> operations) {
        ArrayList<Integer> numClone = new ArrayList<>();
        for (int num : numbers) {
            numClone.add(num);
        }
        ArrayList<Integer> opClone = new ArrayList<>();
        for (int op : operations) {
            opClone.add(op);
        }
        int sum = 0;
        for (int i = 0; i < opClone.size(); i++) {
            int partial = numClone.get(i);
            while (opClone.size() >= i + 1 && opClone.get(i) == 1) {
                partial *= 10;
                partial += numClone.get(i + 1);
                numClone.remove(i + 1);
                opClone.remove(i);
            }
            numClone.set(i, partial);
        }
        sum += numClone.get(0);
        for (int i = 0; i < opClone.size(); i++) {
            if (opClone.get(i) == 2) {
                sum += numClone.get(i + 1);
            }
            if (opClone.get(i) == 3) {
                sum -= numClone.get(i + 1);
            }
        }

        return sum;
    }

}