import java.io.*;
import java.util.*;

public class daisy {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int numFlowers = Integer.parseInt(in.readLine());
        int[] petals = new int[numFlowers];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numFlowers; i++) {
            petals[i] = Integer.parseInt(tokenizer.nextToken());
        }
        long numValid = 0;
        int[][] sums = new int[numFlowers][numFlowers];
        for (int i = 0; i < numFlowers; i++) {
            sums[i][i] = petals[i];
            numValid++;
            for (int j = 1; i + j < numFlowers; j++) {
                sums[i][i + j] = sums[i][i + j - 1] + petals[i + j];
                //System.out.println(i + " " + (i + j) + " " + sums[i][i + j]);
                for (int k = i; k <= i + j; k++) {
                    if (petals[k] == sums[i][i + j] * 1.0 / (j + 1)) {
                        numValid++;
                        //System.out.println(i + " " + (i + j) + " " + sums[i][i + j]);
                        break;
                    }
                }

            }
        }
        System.out.println(numValid);

        in.close();
        // out.close();
    }
}