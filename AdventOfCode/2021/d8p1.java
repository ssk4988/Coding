import java.io.*;
import java.util.*;

public class d8p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d8p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        int answer = 0;
        for (String s : input) {
            String[] s2 = s.split("");
            StringTokenizer tokenizer = new StringTokenizer(s.substring(s.indexOf("|")));
            while (tokenizer.hasMoreTokens()) {
                String s3 = tokenizer.nextToken();
                //System.out.println(s3);
                if (s3.length() == 2 || s3.length() == 3 || s3.length() == 4 || s3.length() == 7) {
                    answer++;
                }
            }
        }
        System.out.println(answer);
        in.close();
    }

}
