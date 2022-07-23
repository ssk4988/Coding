import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringBuilder b = new StringBuilder();
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        boolean encode = tokenizer.nextToken().charAt(0) == 'E';
        String s = tokenizer.nextToken();
        if(encode){
            int i = 0;
            int freq = 1;
            char curr = s.charAt(0);
            while(i < s.length()){
                freq = 1;
                curr = s.charAt(i);
                while(i + 1 < s.length() && s.charAt(i+1) == curr){
                    freq++;
                    i++;
                }
                b.append(curr);
                b.append(freq);
                i++;
            }
            b.append("\n");
        }
        else{
            for(int i = 0; i < s.length(); i++){
                char curr = s.charAt(i);
                if(i + 1 < s.length() && s.charAt(i+1)>='1' && s.charAt(i+1) <= '9'){
                    int val = s.charAt(i+1) - '0';
                    for(int j = 0; j < val; j++){
                        b.append(curr);
                    }
                    i++;
                    continue;
                }
                b.append(curr);
            }
            b.append("\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}