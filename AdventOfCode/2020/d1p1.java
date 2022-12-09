import java.io.*;
import java.util.*;

public class d1p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d1p1.in"));
        ArrayList<Integer> numbers = new ArrayList<>();
        String line = "";
        while ((line = in.readLine()) != null) {
            numbers.add(Integer.parseInt(line));
        }
        Collections.sort(numbers);
        outer: for (int i = 0; i < numbers.size(); i++) {
            int k = numbers.size() - 1;
            for (int j = i + 1; j < numbers.size(); j++) {
                while (k - 1 > j && numbers.get(i) + numbers.get(j) + numbers.get(k) > 2020) {
                    k--;
                }
                if (numbers.get(i) + numbers.get(j) + numbers.get(k) == 2020) {
                    System.out.println(numbers.get(i) * numbers.get(j) * numbers.get(k));
                    break outer;
                }
            }
        }

        in.close();
    }
}