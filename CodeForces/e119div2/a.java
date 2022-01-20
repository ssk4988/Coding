import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            String s = in.readLine();
            int n = 0;
            int e = 0;
            for(int i = 0; i < s.length(); i++){
                if(s.charAt(i) == 'N'){
                    n++;
                }
                else{
                    e++;
                }
            }
            if(n != 1){
                System.out.println("YES");
            }
            else{
                System.out.println("NO");
            }
        }
        in.close();
        out.close();
    }
}