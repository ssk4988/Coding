import java.io.*;
import java.util.*;

public class a2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int aw = 0, ab = 0, bw = 0, bb = 0, cnt = 0, times = 1, val = 1;
            while(n > 0){
                int rem = Math.min(val, n);
                int numblac = 0, numwhite = 0;
                numblac = numwhite = rem / 2;
                if((aw + ab + bw + bb) % 2 == 0){
                    if(rem % 2 == 1) numwhite++;
                }
                else{
                    if(rem % 2 == 1) numblac++;
                }
                if(cnt == 0){
                    ab += numwhite;
                    aw += numblac;
                }
                else{
                    bb += numblac;
                    bw += numwhite;
                } 
                n -= rem;
                val++;
                times++;
                if(times >= 2){
                    times = 0;
                    cnt = 1 - cnt;
                }
            }
            System.out.println(ab + " " + aw + " " + bw + " " + bb);
        }
        in.close();
    }
}
