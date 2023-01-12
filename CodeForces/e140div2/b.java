import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            ArrayList<Long> arr = new ArrayList<>();
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                arr.add(Long.parseLong(tokenizer.nextToken()));
            }
            long val = arr.get(0);
            Collections.sort(arr);
            
            for(int i = 1; i < n; i++){
                if(arr.get(i) > val){
                    if((arr.get(i) - val) % 2 == 0){
                        val = (arr.get(i) + val) / 2;
                    }
                    else{
                        val = val + 1 + (arr.get(i) - val) / 2;
                    }
                }
            }
            out.append(val + "\n");
        }
        System.out.print(out);
        in.close();
    }
}