import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int cn = 0; cn < nc; cn++) {
            String s = in.readLine();
            b.append(s);
            for(int i = s.length() - 1; i >= 0; i--){
                b.append(s.charAt(i));
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
    }
}