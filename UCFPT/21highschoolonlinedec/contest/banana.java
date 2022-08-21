import java.io.*;
import java.util.*;

public class banana {
    public static ArrayList<Integer> p = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int casenums = Integer.parseInt(in.readLine());
        for (int i = 0; i < casenums; i++) {
            p = new ArrayList<>();
            int nbananas = Integer.parseInt(in.readLine());
            int[] bx = new int[nbananas];
            int[] by = new int[nbananas];
            int[] sx = new int[nbananas];
            int[] sy = new int[nbananas];
            for (int j = 0; j < nbananas; j++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                bx[j] = Integer.parseInt(tokenizer.nextToken());
                by[j] = Integer.parseInt(tokenizer.nextToken());
            }
            for (int j = 0; j < nbananas; j++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                sx[j] = Integer.parseInt(tokenizer.nextToken());
                sy[j] = Integer.parseInt(tokenizer.nextToken());
            }
            double[][] dist = new double[nbananas][nbananas];
            for (int j = 0; j < nbananas; j++) {
                for (int k = 0; k < nbananas; k++) {
                    dist[j][k] = Math.sqrt(Math.pow(bx[j] - sx[k], 2) + Math.pow(by[j] - sy[k], 2));
                }
            }
            ArrayList<Integer> arr = new ArrayList<>();
            boolean[] used = new boolean[nbananas];
            permute(arr, 0, used);
            double minDist = Double.MAX_VALUE;
            for (int j = 0; j < p.size() / nbananas; j++) {
                double answer = 0;
                for (int k = 0; k < nbananas; k++) {
                    answer += dist[k][p.get(j * nbananas + k)];
                }
                // System.out.println("answer: " + answer);
                minDist = Math.min(minDist, answer);
            }
            System.out.printf("%.6f%n", minDist);
        }

        in.close();
        out.close();
    }

    public static void permute(ArrayList<Integer> arr, int index, boolean[] used) {
        if (index == used.length) {
            p.addAll(arr);
        }
        for (int i = 0; i < used.length; i++) {
            if (used[i])
                continue;
            used[i] = true;
            arr.add(i);
            permute(arr, index + 1, used);
            arr.remove(index);
            used[i] = false;
        }
    }
}