import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int[] perm = new int[n];
            int[] reverse = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                perm[i] = Integer.parseInt(tokenizer.nextToken())-1;
                reverse[perm[i]] = i;
            }
            String s = in.readLine();
            Set<Integer> no = new TreeSet<>();
            Set<Integer> yes = new TreeSet<>();
            for(int i = 0; i < n; i++){
                if(s.charAt(i) == '0'){
                    no.add(perm[i]);
                }
                else{
                    yes.add(perm[i]);
                }
            }
            int count = 0;
            for(int a : no){
                perm[reverse[a]] = count++;
            }
            for(int a : yes){
                perm[reverse[a]] = count++;
            }
            for(int i = 0; i < n; i++){
                b.append((perm[i] + 1) + (i < n - 1 ? " " : "\n"));
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}