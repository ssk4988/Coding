import java.io.*;
import java.util.*;

public class prob6 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int l = Integer.parseInt(tokenizer.nextToken());
            tokenizer =new StringTokenizer(in.readLine());
            int[] t = new int[n];
            for(int i = 0; i < n; i++){
                t[i] = Integer.parseInt(tokenizer.nextToken());
            }
            Arrays.sort(t);
            int[] np = new int[l + 1];
            int[] lp = new int[l + 1];
            int[] tt = new int[l + 1];
            Arrays.fill(np, Integer.MIN_VALUE);
            Arrays.fill(lp, Integer.MAX_VALUE);
            Arrays.fill(tt, Integer.MAX_VALUE);
            np[0] = 0;
            lp[0] = 0;
            tt[0] = 0;
            for(int i = 0; i < n; i++){
                for(int j = np.length - 1 - t[i]; j >= 0; j--){
                    if(np[j] == Integer.MIN_VALUE) continue;
                    if(np[j + t[i]] < np[j] + 1 || (np[j + t[i]] == np[j] + 1 && tt[j + t[i]] > tt[j] + j + t[i])){
                        np[j+t[i]] = np[j] +1;
                        tt[j + t[i]] = tt[j] + j + t[i];
                        lp[j+t[i]] = j+t[i];
                    }
                }
            }
            int min = 0;
            for(int j = 0; j < np.length; j++){
                if(np[j] > np[min] || (np[j] == np[min] && tt[j] < tt[min])){
                    min = j;
                }
            }
            //System.out.println(Arrays.toString(dp));
            System.out.printf("Case %d: %d %d %d\n", (casenum+1), np[min], lp[min], tt[min]);
        }

        in.close();
        out.close();
    }
}