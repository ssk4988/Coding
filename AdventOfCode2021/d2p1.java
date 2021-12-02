import java.io.*;
import java.util.*;

public class d2p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d2p1.in"));
        String line;
        int hor = 0;
        int ver = 0;
        while ((line = in.readLine()) != null) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            String dir = tokenizer.nextToken();
            int mag = Integer.parseInt(tokenizer.nextToken());
            if (dir.equals("forward")) {
                hor += mag;
            }
            if (dir.equals("up")) {
                ver -= mag;
            }
            if (dir.equals("down")) {
                ver += mag;
            }
        }
        System.out.println(ver * hor);

        in.close();
    }

}
