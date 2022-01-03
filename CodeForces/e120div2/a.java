import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] arr = new int[3];
            for(int i = 0; i < 3; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            Arrays.sort(arr);
            boolean works = (arr[0]+arr[1]+arr[2])%2==0;
            if(works){
                works = false;
                test: for(int i = 0; i < 3; i++){
                    for(int j = 0; j < i; j++){
                        if(arr[3 - i - j] == arr[i] + arr[j] || arr[i] == arr[j]){
                            works = true;
                            break test;
                        }
                    }
                }
            }
            if(works){
                System.out.println("yes");
            }
            else{
                System.out.println("no");
            }
        }
        in.close();
        out.close();
    }
}