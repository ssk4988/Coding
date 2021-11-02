import java.io.*;
import java.util.*;

public class moobuzz {
    public static void main(String[] args) throws Exception {

        BufferedReader in = new BufferedReader(new FileReader("moobuzz.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moobuzz.out")));
        int n = Integer.parseInt(in.readLine());
        ArrayList<Integer> nums = new ArrayList<>();
        for (int i = 1; i <= 15; i++) {
            if (i % 3 != 0 && i % 5 != 0) {
                nums.add(i);
            }
        }
        n--;
        out.println((n / nums.size()) * 15 + nums.get(n % nums.size()));
        in.close();
        out.close();

    }
}