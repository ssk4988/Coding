import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int len =Integer.parseInt(in.readLine());
            int[] arr = new int[len];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < len; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            boolean possible = true;
            if(len == 1){
                possible = true;
            }
            else if(len == 2){
                possible = arr[0] <= arr[1];
            }
            else if(len == 3){
                int[] newArr = new int[len];
                for(int i= 0; i < len; i++){
                    newArr[i] = arr[i];
                }
                int numFix = 0;
                Arrays.sort(newArr);
                for(int i = 0; i < len; i++){
                    if(newArr[i] == arr[i]){
                        numFix++;
                    }
                }
                possible = (numFix % len == 0);
            }
            else{
                possible = true;
            }
            System.out.println(possible ? "YES" : "NO");
        }

        in.close();
        out.close();
    }
}