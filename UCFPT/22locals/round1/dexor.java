import java.io.*;
import java.util.*;

public class dexor {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s1 = in.readLine();
        String s2 = in.readLine();
        int len = Math.max(s1.length(), s2.length());
        while(s1.length() < len){
            s1 = "0" + s1;
        }
        while(s2.length() < len){
            s2 = "0"+s2;
        }
        String ans = "";
        for(int i = 0; i < len; i++){
            int a = s1.charAt(i)-'0';
            int b = s2.charAt(i)-'0';
            if((a <= 2 && b <= 2)||(a>=7 && b>=7)){
                ans += "0";
            }
            else{
                ans += "9";
            }
        }
        System.out.println(ans);
        in.close();
    }
}