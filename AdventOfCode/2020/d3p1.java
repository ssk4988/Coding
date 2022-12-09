import java.io.*;
import java.util.*;

public class d3p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d3p1.in"));

        String line = in.readLine();
        int width = line.length();
        int height = 1;
        ArrayList<char[]> data = new ArrayList<>();
        data.add(line.toCharArray());
        while ((line = in.readLine()) != null) {
            data.add(line.toCharArray());
            height++;
        }
        int[][] slopes = { { 1, 1 }, { 3, 1 }, { 5, 1 }, { 7, 1 }, { 1, 2 } };
        int[] numTrees = new int[5];
        for (int i = 0; i < 5; i++) {
            int x = slopes[i][0];
            int y = slopes[i][1];
            while (y < height) {
                if (data.get(y % height)[x % width] == '#')
                    numTrees[i]++;
                x += slopes[i][0];
                y += slopes[i][1];
            }
            System.out.println(numTrees[i]);
        }
        long prod = 1;
        for (int i = 0; i < numTrees.length; i++) {
            prod *= numTrees[i];
            System.out.println(prod + " " + numTrees[i]);
        }
        System.out.println(prod);
        in.close();
    }

}
