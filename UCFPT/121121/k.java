import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        ArrayList<String> lines =new ArrayList<>();
        for(int i= 0; i < n; i++){
            char[] s= in.readLine().toCharArray();
            StringBuilder b = new StringBuilder();
            for(int j = s.length - 1; j >= 0; j--){
                b.append(s[j]);
            }
            lines.add(b.toString());
        }
        Collections.sort(lines);
        for(String s : lines){
            out.append(s + "\n");
        }
        System.out.print(out);
        in.close();
    }
}