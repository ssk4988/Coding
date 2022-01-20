import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int low = 1;
        int high = n - 1;
        int sum = 0;
        int div = 0;
        while(low < high){
            int mid = (low + high + 1) / 2; //max is n - 1
            //System.out.println(low + " " + mid + " " + high);
            int q = n - (sum + mid) % n; // chances of mid == n - 1 and sum % n == 1
            System.out.println("+ " + q);
            System.out.flush();
            int val = Integer.parseInt(in.readLine());
            if(val > div){
                low = mid;
            }
            else{
                high = mid - 1;
            }
            sum += q;
            div = val;
        }
        System.out.println("! " + (low+sum));
        in.close();
        out.close();
    }
}