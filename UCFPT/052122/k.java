import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] cnt =new int[26];
        String[] str = new String[n];
        for(int i = 0; i < n; i++){
            String s = in.readLine();
                cnt[s.charAt(0)-'A']++;
            str[i] = s;
        }
        boolean works = false;
        for(int i = 0; i <n; i++){
            boolean w = true;
            for(int j = 0; j < str[i].length(); j++){
                if(cnt[str[i].charAt(j)-'A']<= 0) w = false;
            }
            if(w) works = true;
        }
        System.out.println(works ? "Y" : "N");
        in.close();
    }
}