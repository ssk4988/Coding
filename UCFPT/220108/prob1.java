import java.io.*;
import java.util.*;

public class prob1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;

        ArrayList<String> input = new ArrayList<>();

        while ((line = in.readLine()) != null && line.length() > 0) {
            // System.out.println(line);
            StringBuilder b = new StringBuilder();
            for (int i = 0; i < line.length(); i += 2) {
                b.append((char) (Integer.parseInt(line.substring(i, i + 2), 16)));
            }
            b.append("\n");
            System.out.print(b);
        }

        in.close();
        out.close();
    }
}