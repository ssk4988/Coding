import java.io.*;
import java.util.*;

public class d10p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d10p1.in"));
        ArrayList<Integer> jolts = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            jolts.add(Integer.parseInt(line));
        }
        jolts.add(0);
        Collections.sort(jolts);
        jolts.add(jolts.get(jolts.size() - 1) + 3);
        int[] diff = new int[4];
        for (int i = 1; i < jolts.size(); i++) {
            diff[jolts.get(i) - jolts.get(i - 1)]++;
        }
        System.out.println(diff[1] * diff[3]);
        ArrayList<Long> ways = new ArrayList<>();
        for (int i = 0; i < jolts.size(); i++) {
            ways.add(0l);
        }
        ways.set(jolts.size() - 1, 1l);
        for (int i = jolts.size() - 2; i >= 0; i--) {
            for (int j = i + 1; j < jolts.size() && jolts.get(j) - jolts.get(i) <= 3; j++) {
                ways.set(i, ways.get(i) + ways.get(j));
            }
        }
        System.out.println(ways.get(0));

        in.close();
    }

}
