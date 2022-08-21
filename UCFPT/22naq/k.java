import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int q = Integer.parseInt(tokenizer.nextToken());
        int[] arr = new int[n];
        tokenizer = new StringTokenizer(in.readLine());
        for(int i= 0; i < n; i++){
            arr[i] = Integer.parseInt(tokenizer.nextToken());
        }
        for(int i = 0; i < q; i++){
            int query = Integer.parseInt(in.readLine());
            int curr = 0;
            int left = 0;
            int right = n-1;
            boolean found = query == 0;
            while(left < n && !found){
                while(left <= right && curr < query){
                    curr += arr[right--];
                }
                if(curr == query){
                    found = true;
                }
                while(right+1 < n && curr > query){
                    right++;
                    curr -= arr[right];
                }
                if(curr == query){
                    found = true;
                }
                curr += arr[left++];   
                while(right+1 < left){
                    right++;
                    curr -= arr[right];
                } 
                if(curr == query){
                    found = true;
                } 
            }
            if(found){
                System.out.println("Yes");
            }
            else{
                System.out.println("No");
            }
        }

        in.close();
        out.close();
    }
}