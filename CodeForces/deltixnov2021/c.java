import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int e = Integer.parseInt(tokenizer.nextToken());
            int[] arr = new int[n];
            boolean[] isPrime = new boolean[n];
            boolean[] isOne = new boolean[n];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                isPrime[i] = isPrime(arr[i]);
                isOne[i] = arr[i] == 1;
            }
            int answer = 0;
            int p1 = 0;
            int p2 = 0;
            int numPrimes = 0;
            int pindex = -1;
            while (p1 < n) {
                numPrimes = 0;
                while(p1 + 1 < n && !(isPrime[p1]||isOne[p1])){
                    p1++;
                }
                if(!(isPrime[p1]||isOne[p1])){
                    break;
                }
                p2 = p1;
                while (p2 + 1 < n && numPrimes == 0 && (isPrime[p2 + 1] || isOne[p2 + 1])) {
                    p2++;
                    if (isPrime[p2]) {
                        pindex = p2;
                        numPrimes++;
                    }
                }
                if(!isPrime[p2]){
                    p1 = p2+1;
                    continue;
                }
                for (int i = pindex; i <= p2; i++) {

                }
                if (isPrime[p1]) {
                    pindex = -1;
                    numPrimes--;
                }
                p1++;
            }
        }

        in.close();
        out.close();
    }

    public static boolean isPrime(int k) {
        if (k < 2)
            return false;
        if (k == 2 || k == 3)
            return true;
        for (int i = 3; i * i <= k; i += 2) {
            if (k % i == 0)
                return false;
        }
        return true;
    }
}