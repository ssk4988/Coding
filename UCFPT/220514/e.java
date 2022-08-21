import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            String l = in.readLine();
            for(int i = 0; i < l.length(); i++){
                if(l.charAt(i) == ',' && (i + 1 >= l.length() || l.charAt(i + 1) == ',')){
                    l = l.substring(0, i+1) + "0" + l.substring(i+1);
                }
            }
            StringTokenizer tokenizer =new StringTokenizer(l, ",");
            int dig = tokenizer.countTokens();
            long num = 0;
            long mult = 1;
            for(int i = 0; i+1 < dig; i++){
                mult *= 60;
            }
            for(int i = 0; i < dig; i++){
                String s = tokenizer.nextToken();
                if(s.length() > 0){
                    num += mult * Integer.parseInt(s);
                }
                mult /= 60;
            }
            System.out.println(num);
        }
        in.close();
    }
}