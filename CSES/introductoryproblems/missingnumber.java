import java.io.*;
import java.util.*;

public class missingnumber {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        boolean[] contains = new boolean[n];
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        for(int i = 0; i < n-1; i++){
            contains[Integer.parseInt(tokenizer.nextToken())-1]=true;
        }
        for(int i = 0; i < n; i++){
            if(!contains[i]){
                System.out.println(i+1);
                break;
            }
        }
        in.close();
    }
}