import java.io.*;
import java.util.*;

public class d9p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d9p1.in"));
        ArrayList<Long> numbers = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            numbers.add(Long.parseLong(line));
        }
        long num = 0;
        int index = 0;
        for (int i = 25; i < numbers.size(); i++) {
            boolean works = false;
            for (int j = i - 25; j < i; j++) {
                for (int k = i - 25; k < j; k++) {
                    if (numbers.get(k) + numbers.get(j) == numbers.get(i)) {
                        works = true;
                    }
                }
            }
            if (!works) {
                System.out.println(numbers.get(i));
                num = numbers.get(i);
                index = i;
            }
        }
        int start = 0;
        int end = 0;
        long[][] consecutivesum = new long[numbers.size()][numbers.size()];
        for (int i = 0; i < numbers.size(); i++) {
            consecutivesum[i][0] = numbers.get(i);
            if (consecutivesum[i][0] == num && i != index) {
                start = i;
                end = i;
            }
        }
        int i = 0;
        for (int j = 1; j < numbers.size(); j++) {
            for (i = 0; i + j < numbers.size(); i++) {
                consecutivesum[i][j] = consecutivesum[i][j - 1] + numbers.get(i + j);
                if (consecutivesum[i][j] == num) {
                    start = i;
                    end = i + j;
                }
            }
        }
        long min = Long.MAX_VALUE;
        long max = Long.MIN_VALUE;
        for(int x  = start; x <= end; x++){
            if(numbers.get(x) > max) max = numbers.get(x);
            if(numbers.get(x) < min) min = numbers.get(x);
        }
        System.out.println(min + max);

        in.close();
    }

}
