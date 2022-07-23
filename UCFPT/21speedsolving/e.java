import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] v = new int[n];
        for(int i = 0; i< n; i++){
            v[i] = Integer.parseInt(in.readLine()) - 1;
        }
        int prev = -1;
        int cnt = 1;
        for(int i = 0; i < n; i++){
            if(prev < v[i]){

            }
            else{
                cnt++;
            }
            prev = v[i];
        }
        System.out.println(cnt);

        in.close();
        out.close();
    }
}