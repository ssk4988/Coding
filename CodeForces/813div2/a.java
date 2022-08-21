import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            ArrayList<Integer> original = new ArrayList<>();
            tokenizer =new StringTokenizer(in.readLine());
            int num = 0;
            for(int i = 0; i < n; i++){
                original.add(Integer.parseInt(tokenizer.nextToken()));
                if(i < k && original.get(i) <= k){
                    num++;
                }
            }
            System.out.println(k - num);
        }
        in.close();
    }
}