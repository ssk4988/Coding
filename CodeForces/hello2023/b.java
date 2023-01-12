import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            if(n == 3){
                out.append("NO\n");
                continue;
            }
            out.append("YES\n");
            int f, s;
            if(n % 2 == 0){
                f = 1;
                s = -1;
            }
            else{
                f = -1 * ((n - 2) / 2);
                s = -f + 1;
            }
            for(int i = 0; i < n; i++){
                if(i % 2 == 0){
                    out.append(f);
                }
                else{
                    out.append(s);
                }
                out.append(i + 1 < n ? ' ' : '\n');
            }
        }
        System.out.print(out);
        in.close();
    }
}