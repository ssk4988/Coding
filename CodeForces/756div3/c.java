/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        outer: for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int[] arr = new int[n];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            if(n == 1){
                System.out.println(1);
                continue outer;
            }
            int[] newArr = new int[2*n-1];
            int lp = 0;
            int rp = n-1;
            int nlp = n;
            int nrp = n;
            if(arr[lp] == n){
                newArr[nlp--] = arr[lp++];
                nrp++;
            }
            else if(arr[rp] == n){
                newArr[nrp++] = arr[rp--];
                nlp--;
            }
            else{
                System.out.println(-1);
                continue outer;
            }
            while(lp <= rp){
                if(arr[lp] <= arr[rp]){
                    newArr[nlp--] = arr[lp++];
                }
                else{
                    newArr[nrp++] = arr[rp--];
                }
            }
            nlp++;
            nrp--;
            for(int i = nlp; i <= nrp; i++){
                System.out.print(newArr[i]);
                if(i < nrp) System.out.print(" ");
            }
            System.out.println();
        }
        in.close();
        out.close();
    }
}