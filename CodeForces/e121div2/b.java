import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            String s = in.readLine();
            String max = "";
            boolean dig = false;
            int digindex = 0;
            int oneindex = 0;
            for(int i = s.length() - 2; i>=0; i--){
                int a = (s.charAt(i) - '0') + (s.charAt(i+1) - '0');
                if(a>=10){
                    dig = true;
                    digindex = i;
                    break;
                }
            }
            for(int i = 0; i+1<s.length(); i++){
                int a = (s.charAt(i) - '0') + (s.charAt(i+1) - '0');
                if(a < 10){
                    int a1 = Integer.parseInt(s.substring(i, i+2));
                    if(a > a1){
                        oneindex = i;
                        break;
                    }
                }
            }
            int index = dig ? digindex : oneindex;
            int a = (s.charAt(index) - '0') + (s.charAt(index+1) - '0');
            String ans = s.substring(0, index) + a + s.substring(index + 2);
            String str = max;
            boolean lead = true;
            /*for(int i= 0; i < str.length(); i++){
                if(lead && str.charAt(i)== '0') continue;
                if(lead && str.charAt(i) != '0') lead = false;
                ans.append(str.charAt(i));
            }*/
            b.append(ans + "\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}