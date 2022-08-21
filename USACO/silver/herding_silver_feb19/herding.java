import java.io.*;
import java.util.*;

public class herding {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("herding.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("herding.out")));
        int n = Integer.parseInt(in.readLine());
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(in.readLine());
        }
        Arrays.sort(arr);
        int l = 0;
        int r = 0;

        int max = Math.max(arr[n - 1] - arr[1], arr[n - 2] - arr[0]) - 1 - (n - 3);
        int min = max;
        if (arr[1] - arr[0] == 1)
            l++;
        int upper = n - 1;
        if (arr[n - 1] - arr[n - 2] == 1)
            upper--;
        while (l <= upper && r <= upper) {
            r = Math.max(r, l);
            while (r + 1 <= upper && arr[r + 1] - arr[l] < n)
                r++;
            min = Math.min(min, n - (r - l + 1));
            l++;
        }
        out.println(min);
        out.println(max);
        in.close();
        out.close();
    }
}