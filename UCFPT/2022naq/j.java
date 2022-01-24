import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        Map<Long, tuple> map = new HashMap<>();
        map.put(1L, new tuple("1", 0));
        int n = Integer.parseInt(in.readLine());
        tuple[] tuples = new tuple[n];
        long[] arr = new long[n];
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        for(int i = 0; i < n; i++){
            arr[i] = Long.parseLong(tokenizer.nextToken());
        }
        long plus = 0;
        for(int i = n-1; i >= 0; i--){
            tuples[i] = calc(arr[i] + plus, map);
            plus += tuples[i].plus;
        }
        StringBuilder answer = new StringBuilder();
        for(int i = 0; i < n; i++){
            answer.append(tuples[i].str);
        }
        System.out.println(answer);
        in.close();
        out.close();
    }
    public static tuple calc(long x, Map<Long, tuple> map){
        tuple get = map.get(x);
        if(get != null) return get;
        long x1 = x % 2 == 0 ? x / 2 : x - 1;
        tuple child = calc(x1, map);
        tuple prod = new tuple(child.str.toString(), child.plus);
        if(x%2 == 0){
            prod.str.append("d+");
        }else{
            prod.str.append("1+");
        }
        prod.plus++;

        return prod;
    }
    public static class tuple{
        StringBuilder str;
        long plus;
        public tuple(String str, long plus){
            this.str = new StringBuilder(str);
            this.plus = plus;
        }
    }
}