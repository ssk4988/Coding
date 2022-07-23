import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int[] c = new int[26];
        Arrays.fill(c, 1);
        String s= in.readLine();
        for(int i= 0; i < s.length(); i++){
            c[s.charAt(i)-'a']++;
        }
        long answer = 1;
        long mod = 11092019;
        for(int i = 0; i < c.length; i++){
            answer *=  c[i];
            if(answer > mod){
                answer %= mod;
            }
        }
        System.out.println(answer);

        in.close();
        out.close();
    }
}