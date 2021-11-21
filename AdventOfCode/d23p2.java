import java.io.*;
import java.util.*;

public class d23p2 {
    public static void main(String[] args) throws Exception {
        String input = "487912365";
        int numMoves = 10000000;
        long start = System.currentTimeMillis();

        int min = 1;
        int max = 1000000;
        Cup[] indexOrder = new Cup[max];
        Cup[] valueOrder = new Cup[max];
        for (int i = 0; i < input.length(); i++) {
            int val = Integer.parseInt(input.substring(i, i + 1));
            indexOrder[i] = new Cup(i, val);
        }

        for (int i = 10; i <= max; i++) {
            indexOrder[i - 1] = new Cup(i - 1, i);
        }
        for (int i = 0; i < indexOrder.length; i++) {
            indexOrder[i].right = indexOrder[(i + 1) % indexOrder.length];
            valueOrder[i] = indexOrder[i];
        }
        System.out.println("initialized " + (System.currentTimeMillis() - start));
        Arrays.sort(valueOrder);
        Cup currentCup = indexOrder[0];
        for (int i = 0; i < numMoves; i++) {
            Cup pointer = currentCup;
            /*
            String lString = "";
            String lString2 = "";
            for (int j = 0; j < max; j++) {
                lString += pointer.value + ", ";
                lString2 += pointer.right.value + ", ";
                pointer = pointer.right;
            }
            */
            int searchValue = currentCup.value <= min ? max : currentCup.value - 1;
            boolean shift = false;
            ArrayList<Cup> currentNext3 = new ArrayList<>();
            pointer = currentCup;
            for (int j = 0; j < 3; j++) {
                currentNext3.add(pointer.right);
                pointer = pointer.right;
            }
            while (currentNext3.contains(valueOrder[searchValue - 1])) {
                searchValue = searchValue <= min ? max : searchValue - 1;
                shift = true;
            }
            // System.out.println("Move " + (i + 1) + ": " + currentCup + " " +
            // valueOrder[searchValue - 1]);
            // System.out.println(lString);
            // System.out.println(lString2);
            if (shift) {
                // System.out.println(currentCup.index + " " + currentCup.value + " " +
                // searchValue + " " + i);
            }
            Cup[] oldClock = new Cup[6];
            pointer = currentCup;
            for (int j = 0; j < 3; j++) {
                oldClock[j] = pointer.right;
                pointer = pointer.right;
            }
            currentCup.right = oldClock[2].right;
            pointer = valueOrder[searchValue - 1];
            for (int j = 0; j < 3; j++) {
                oldClock[j + 3] = pointer.right;
                pointer = pointer.right;
            }
            pointer = valueOrder[searchValue - 1];
            valueOrder[searchValue - 1].right = oldClock[0];
            oldClock[2].right = oldClock[3];
            currentCup = currentCup.right;
        }
        Cup pointer = valueOrder[1-1];
        /*
        String lString = "";
        for (int j = 0; j < max; j++) {
            lString += pointer.value;
            pointer = pointer.right;
        }
        System.out.println(lString);
        */
        long num = 1;
        for (int j = 0; j < 3; j++) {
            num *= pointer.value;
            pointer = pointer.right;
        }
        System.out.println(num);
        System.out.println("done " + (System.currentTimeMillis() - start));
    }

    public static class Cup implements Comparable<Cup> {
        int index;
        int value;
        Cup right;

        public Cup(int index, int value) {
            this.index = index;
            this.value = value;
        }

        @Override
        public int compareTo(Cup o) {
            return this.value - o.value;
        }

        @Override
        public String toString() {
            return this.value + " r" + right.value;
        }
    }
}
