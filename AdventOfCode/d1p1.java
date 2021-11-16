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
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < j; k++) {
                    if (numbers.get(i) + numbers.get(j) + numbers.get(k) == 2020) {
                        System.out.println(numbers.get(i) * numbers.get(j) * numbers.get(k));
                    }
                }

            }
        }

        in.close();
    }
}