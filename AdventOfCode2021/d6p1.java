import java.io.*;
import java.util.*;

public class d6p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d6p1.in"));
        String[] s = in.readLine().split(",");
        long[] num = new long[9];
        for (int i = 0; i < s.length; i++) {
            num[Integer.parseInt(s[i])]++;
        }
        int numMoves = 256;
        for (int i = 0; i < numMoves; i++) {
            long[] newArr = new long[9];
            for (int j = 1; j < newArr.length; j++) {
                newArr[j - 1] = num[j];
            }
            newArr[6] += num[0];
            newArr[8] += num[0];
            num = newArr;
        }
        long sum = 0;
        for (long i : num) {
            sum += i;
        }
        System.out.println(sum);
        in.close();
    }
}