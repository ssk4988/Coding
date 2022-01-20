import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            String s = in.readLine();
            int[] frq = new int[26];
            for(int i = 0; i < n; i++){
                frq[s.charAt(i) - 'a']++;
            }
            int numPairs = 0;
            int numOdd = 0;
            for(int i = 0; i < frq.length; i++){
                numPairs += frq[i] / 2;
                numOdd += frq[i] % 2;
            }
            int answer = 2 * (numPairs / k);
            numPairs -= (numPairs / k) * k;
            numOdd += 2 * numPairs;
            numPairs = 0;
            if(numOdd >= k) answer++;
            System.out.println(answer);
        }

        in.close();
        out.close();
    }
}