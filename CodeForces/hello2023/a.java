import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            String s = in.readLine();
            int l = 0, r = 0;
            int lastl = -1, firstr = -1;
            for(int i = 0; i < n; i++){
                if(s.charAt(i) == 'R'){
                    r++;
                    if(firstr == -1) firstr = i;
                }
                else{
                    l++;
                    lastl = i;
                }
            }
            if(l == 0 || r == 0){
                out.append("-1\n");
                continue;
            }
            else if(lastl == 0){
                out.append("1\n");
            }
            else if(firstr == n - 1){
                out.append((n - 1) + "\n");
            }
            else if(lastl < firstr){
                out.append(firstr + "\n");
            }
            else{
                out.append("0\n");
            }
        }
        System.out.print(out);
        in.close();
    }
}