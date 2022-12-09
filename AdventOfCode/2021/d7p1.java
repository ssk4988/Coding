import java.io.*;
import java.util.*;

public class d7p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d7p1.in"));
        String[] list = in.readLine().split(",");
        int[] list2 = new int[list.length];
        int sum = 0;
        for (int i = 0; i < list.length; i++) {
            list2[i] = Integer.parseInt(list[i]);
            sum += list2[i];
        }
        System.out.println(sum);
        Arrays.sort(list2);

        long mean = sum /  list2.length;
        long answer = 0;
        System.out.println(mean);
        for (int i = 0; i < list.length; i++) {
            answer += Math.abs(list2[i] - mean) * (Math.abs(list2[i] - mean) + 1) / 2;
        }
        System.out.println(answer);

        in.close();
    }

}
