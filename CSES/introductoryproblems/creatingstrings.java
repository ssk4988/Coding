import java.io.*;
import java.util.*;

public class creatingstrings {
    public static int cnt = 0;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s = in.readLine();
        int[] freq = new int[26];
        for(int i = 0; i < s.length(); i++){
            freq[s.charAt(i)-'a']++;
        }
        StringBuilder b = new StringBuilder();
        solve(new int[26], freq, b, s.length(), "");
        System.out.println(cnt);
        System.out.print(b);
        in.close();
    }
    public static void solve(int[] used, int[] freq, StringBuilder b, int n, String curr){
        if(curr.length() >= n){
            b.append(curr + "\n");
            cnt++;
            return;
        }
        for(int i = 0; i < freq.length; i++){
            if(used[i] < freq[i]){
                used[i]++;
                curr += (char)('a'+i);
                solve(used, freq, b, n, curr);
                curr = curr.substring(0, curr.length() - 1);
                used[i]--;
            }
        }
    }
}