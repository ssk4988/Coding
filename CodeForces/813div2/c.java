import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out =new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int[] arr = new int[n];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            HashSet<Integer> cur =new HashSet<>();
            HashSet<Integer> add = new HashSet<>();
            for(int i = 0; i < n; i++){
                //if(arr[i] > arr[i+1]) maxinv = i;
                add.add(arr[i]);
                if(cur.contains(arr[i]) || (i + 1 < n && arr[i] > arr[i+1])){
                    cur.addAll(add);
                    add.clear();
                }
            }
            out.append(cur.size() + "\n");
        }
        System.out.print(out);
        in.close();
    }
}