import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] arr = new int[n];
        for(int i = 0; i < n; i++){
            arr[i] = Integer.parseInt(in.readLine());
        }
        Arrays.sort(arr);
        int i1 = 0;
        int i2 = n-1;
        int min = Integer.MAX_VALUE;
        while(i1 < i2){
            min = Math.min(min, arr[i1++] + arr[i2--]);
        }        
        System.out.println(min);
        in.close();
    }
}