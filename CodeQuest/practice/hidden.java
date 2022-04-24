import java.util.*;
import java.io.*;

public class hidden {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int length = Integer.parseInt(in.readLine()) - 1;
        String alphabet = in.readLine();
        for (int i = 0; i < length; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            while (tokenizer.hasMoreTokens()) {
                String word = tokenizer.nextToken();
                String[] chars = word.split("-");
                for (int j = 0; j < chars.length; j++) {
                    b.append(alphabet.charAt(Integer.parseInt(chars[j]) - 1));
                }
                if(tokenizer.hasMoreTokens()){
                    b.append(" ");
                }
            }
            b.append("\n");
        }

        System.out.print(b);
        in.close();
    }
}