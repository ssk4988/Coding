import java.io.*;
import java.util.*;

public class d15p1 {
    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("d15p1.in"));
        String[] str = in.readLine().split(",");
        int[] start = new int[str.length];
        ArrayList<Integer> numbers = new ArrayList<>();
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < str.length; i++) {
            if (numbers.size() > 0) {
                int prevNumber = numbers.get(numbers.size() - 1);
                map.put(prevNumber, numbers.size() - 1);
            }
            start[i] = Integer.parseInt(str[i]);
            numbers.add(start[i]);
        }
        int limit = 30000000;
        while (numbers.size() < limit) {
            int prevNumber = numbers.get(numbers.size() - 1);
            if (!map.containsKey(prevNumber)) {
                map.put(prevNumber, numbers.size() - 1);
                numbers.add(0);
            } else {
                int prevIndex = map.get(prevNumber);
                map.put(prevNumber, numbers.size() - 1);
                numbers.add(numbers.size() - 1 - prevIndex);
            }

            // if(numbers.size() % 1000000 == 0) System.out.println(numbers.size()/ 1000000
            // * 100 /( limit / 1000000));
            // System.out.println(numbers.get(numbers.size() - 1));
            // System.out.println(map.get(numbers.get(numbers.size() - 1)));
        }
        System.out.println((System.currentTimeMillis() - start_time) / 1000);
        System.out.println(numbers.get(limit - 1));

        in.close();
    }
}
