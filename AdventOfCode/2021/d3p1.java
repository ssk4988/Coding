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
        int epsilon = 0;
        for (int i = 0; i < size; i++) {
            int bit = 1 << (size - 1 - i);
            if (common[i] * 2 <= inputs.size()) {
                epsilon |= bit;
            }
        }
        ArrayList<Integer> inputscl = new ArrayList<>();
        inputscl.addAll(inputs);
        for (int i = 0; i < size; i++) {
            ArrayList<Integer> newList = new ArrayList<>();
            int bit = 1 << (size - 1 - i);
            int val = 0;
            for (int s1 : inputscl) {
                if ((s1 & bit) == bit)
                    val++;
            }
            int bit2 = (2 * val >= inputscl.size() ? 1 : 0) << (size - 1 - i);
            for (int j = 0; j < inputscl.size(); j++) {
                if (bit2 == (bit & inputscl.get(j)))
                    newList.add(inputscl.get(j));
            }
            inputscl = newList;
            if (inputscl.size() == 1)
                break;
        }
        int oxyrating = inputscl.get(0);
        inputscl = new ArrayList<>();
        inputscl.addAll(inputs);
        for (int i = 0; i < size; i++) {
            ArrayList<Integer> newList = new ArrayList<>();
            int bit = 1 << (size - 1 - i);
            int val = 0;
            for (int s1 : inputscl) {
                if ((s1 & bit) == bit)
                    val++;
            }
            int bit2 = (2 * val >= inputscl.size() ? 0 : 1) << (size - 1 - i);
            for (int j = 0; j < inputscl.size(); j++) {
                if (bit2 == (bit & inputscl.get(j)))
                    newList.add(inputscl.get(j));
            }
            inputscl = newList;
            if (inputscl.size() == 1)
                break;
        }
        int co2rating = inputscl.get(0);
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
