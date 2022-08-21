import java.io.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int i = Integer.parseInt(in.readLine());
        int count = 0;
        while(i >= 10){
            int j = 1;
            int k = i;
            while(k > 0){
                j *= k - k/10*10;
                k/=10;
            }
            i = j;
            count++;
        }
        System.out.println(count);

        in.close();
    }
}