import java.io.*;
import java.util.*;

public class encode {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b= new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            String text = in.readLine();
            String key = in.readLine();
            int[] shift = new int[key.length()];
            for(int i = 0; i < shift.length; i++){
                shift[i] = key.charAt(i) - 'A';
            }
            int curr = 0;
            for(int i = 0; i < text.length(); i++){
                if(text.charAt(i) == ' '){
                    b.append(' ');
                    continue;
                }
                int c = text.charAt(i) - 'A';
                c += shift[curr++];
                curr %= shift.length;
                c %= 26;
                b.append((char)(c + 'A'));
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}