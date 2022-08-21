import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String alp = in.readLine();
        char[] a = new char[alp.length()];
        for(int i = 0; i < alp.length(); i++){
            a[i] = alp.charAt(i);
        }
        String s = in.readLine();
        Set<String> answer = new TreeSet<>();
        for(int i= 0; i < s.length(); i++){
            answer.add(s.substring(0, i) + (i+1 < s.length() ? s.substring(i+1) : ""));
            for(int j = 0; j < a.length; j++){
                if(a[j] == s.charAt(i)) continue;
                answer.add(s.substring(0, i) + a[j] +  (i+1 < s.length() ? s.substring(i+1) : ""));
            }
        }
        for(int i = 0; i < s.length() + 1; i++){
            for(int j=  0; j < a.length; j++){
                answer.add(s.substring(0, i) + a[j] + (i < s.length() ? s.substring(i) : ""));
            }
        }
        for(String k : answer){
            System.out.println(k);
        }


        in.close();
        out.close();
    }
}