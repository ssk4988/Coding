import java.io.*;
import java.util.*;

public class d5p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d5p1.in"));
        int maxAnswer = 0;
        String line = "FBFBBFFRLR";
        boolean[] seats = new boolean[981];
        while ((line = in.readLine()) != null) {
            String rowstr = line.substring(0, 7);
            String colstr = line.substring(7, line.length());
            int row = 0;
            int inc = 64;
            for (int i = 0; i < rowstr.length(); i++) {
                if (rowstr.charAt(i) == 'B') {
                    row += inc;
                }
                inc /= 2;
            }
            int col = 0;
            inc = 4;
            for (int i = 0; i < colstr.length(); i++) {
                if (colstr.charAt(i) == 'R') {
                    col += inc;
                }
                inc /= 2;
            }
            int ans = row * 8 + col;
            seats[ans] = true;
            if (ans > maxAnswer)
                maxAnswer = ans;
        }
        System.out.println(maxAnswer);
        for (int i = 1; i < seats.length - 1; i++) {
            if (seats[i - 1] && seats[i + 1] && !seats[i]) {
                System.out.println(i);
            }
        }
        in.close();
    }

}
