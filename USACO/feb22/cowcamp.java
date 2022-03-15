import java.io.*;
import java.util.*;

public class cowcamp {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int t = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        double[][] p = new double[t + 5][t + 5];
        p[1][1] = 1;
        for (int i = 1; i + 1 <= t; i++) {
            for (int j = 1; j <= i; j++) {
                p[i + 1][j] += 0.5 * p[i][j];
                p[i + 1][j + 1] += 0.5 * p[i][j];
            }
        }
        double[] pless = new double[t + 1]; // pless[i] = prob that x < i
        double[] pge = new double[t + 1]; // pge[i] = prob that x >= i
        for (int i = 1; i < pless.length; i++) {
            pless[i] = pless[i - 1] + p[t][i-1];
        }
        pge[pge.length - 1] = p[t][t];
        for (int i = t - 1; i >= 0; i--) {
            pge[i] = pge[i + 1] + p[t][i];
        }
        //System.out.println(Arrays.toString(pless));
        double[] e = new double[t + 1]; // e[i] = expected value if only possible that x >= i, e[0,1] = e[x]
        for (int i = 0; i < e.length; i++) {
            for (int j = t; j >= i; j--) {
                e[i] += j * p[t][j];
            }
            e[i] /= pge[i];
        }
        //System.out.println(Arrays.toString(e));
        int k2 = k;
        k2--;
        double curre = e[1];
        int target = (int) Math.ceil(e[1]);
        while (k2 > 0 && target <= t) {
            //System.out.println("target: " + target + " left: " + k2 + " curre" + curre);
            int low = 0;
            int high = k2 + 1;
            while (low < high) {
                int mid = low + (high - low) / 2;
                double next = curre * Math.pow(pless[target], mid) + e[target] * (1 - Math.pow(pless[target], mid));
                //System.out.println("curre " + curre + " pless " + pless[target] + " mid " + mid + " etarget " + e[target]);
                //System.out.println("mid " + mid + " e " + next);
                if (next >= target) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            // ans = Math.min(k2, low)
            
            int ans = Math.min(k2, low);
            
            curre = curre * Math.pow(pless[target], ans) + e[target] * (1 - Math.pow(pless[target], ans));
            //System.out.println("ans " + ans + " e " + curre);
            k2 -= ans;
            target++;
        }
        System.out.println(curre);
        in.close();
    }
}