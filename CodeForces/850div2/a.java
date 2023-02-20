import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int a = 0, b = 0, cnt = 0, times = 1, val = 1;
            while(n > 0){
                int rem = Math.min(val, n);
                if(cnt == 0){
                    a += rem;
                }
                else{
                    b += rem;
                } 
                n -= rem;
                val++;
                times++;
                if(times >= 2){
                    times = 0;
                    cnt = 1 - cnt;
                }
            }
            System.out.println(a + " " + b);
        }
        in.close();
    }
}
