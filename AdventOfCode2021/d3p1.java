import java.io.*;
import java.util.*;

public class d3p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d3p1.in"));
        String line;
        ArrayList<Integer> inputs = new ArrayList<>();
        int size = -1;
        while ((line = in.readLine()) != null) {
            if (size == -1)
                size = line.length();
            inputs.add(Integer.parseInt(line, 2));
        }
        int gamma = 0;
        int[] common = new int[size];
        for (int i = 0; i < size; i++) {
            int bit = 1 << (size - 1 - i);
            for (int j = 0; j < inputs.size(); j++) {
                if ((bit & inputs.get(j)) == bit) {
                    common[i]++;
                }
            }
            if (common[i] * 2 >= inputs.size()) {
                gamma |= bit;
            }
        }
        int com = 0;
        for (int i = 0; i < size; i++) {
            int bit = 1 << (size - 1 - i);
            if (common[i] * 2 >= inputs.size()) {
                com |= bit;
            }
        }
        int oxyrating = 0;
        int oxymax = 0;
        for (int j = 0; j < inputs.size(); j++) {
            int curr = 0;
            for (int i = 0; i < size; i++) {
                int bit = 1 << (size - 1 - i);
                if ((bit & com) == (bit & inputs.get(j))) {
                    curr++;
                } else {
                    break;
                }
            }
            if (curr > oxymax) {
                oxymax = curr;
                oxyrating = inputs.get(j);
            }
        }
        int co2rating = 0;
        int co2max = 0;
        for (int j = 0; j < inputs.size(); j++) {
            int curr = 0;
            for (int i = 0; i < size; i++) {
                int bit = 1 << (size - 1 - i);
                if ((bit & inputs.get(j)) == (common[i] * 2 > inputs.size() ? 1 : 0) << (size - i - 1)) {
                    curr++;
                } else {
                    break;
                }
            }
            if (curr > co2max) {
                co2max = curr;
                co2rating = inputs.get(j);
            }
        }

        int mask = 1 << size;
        mask--;
        int epsilon = ~gamma & mask;
        System.out.println("oxygen: " + oxyrating);
        System.out.println("co2 " + co2rating);
        System.out.println("prod: " + (oxyrating * co2rating));
        System.out.println("len: " + size);
        System.out.println(inputs.size() + "numbers");
        System.out.println(Arrays.toString(common));
        System.out.println("gamma: " + gamma + " epsilon " + gamma);
        System.out.println((long) epsilon * gamma);

        in.close();
    }

}
