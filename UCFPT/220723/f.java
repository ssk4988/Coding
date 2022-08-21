import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // long n = Long.parseLong(in.readLine());
        for (int i = 0; i < 100; i++) {
            solve(i);
        }

        in.close();
    }

    public static void solve(long n) {
        long[] cnt = new long[2];
        if (n <= 1) {
            cnt[1] = n;
        } else {
            ArrayList<Long> f = new ArrayList<>();
            f.add(1L);
            f.add(1L);
            long sum = 3;
            while (sum < n) {
                f.add(f.get(f.size() - 2) + f.get(f.size() - 1));
                sum += f.get(f.size() - 1) * (f.size());
            }
            int len = f.size();
            while (sum >= n) {
                sum -= f.get(f.size() - 1) * (f.size());
            }

            long place = (n - sum - 1) / (len);

            long digs = (n - sum - 1) % len;
            // System.out.println(sum + " " + place + " " + digs + " " + len);
            long[] zero = new long[len + 1];
            long[] one = new long[len + 1];
            long[] onesum = new long[len + 1];
            long[] zerosum = new long[len + 1];
            one[1] = zero[0] = zero[1] = zerosum[0] = 1;
            onesum[1] = 1;
            zerosum[1] = 2;
            for (int i = 2; i < one.length; i++) {
                one[i] = onesum[i - 2] + f.get(i - 1);
                zero[i] = f.get(i - 1) * i;
                onesum[i] = one[i] + onesum[i - 1];
                zerosum[i] = zero[i] + zerosum[i - 1];
            }
            f.add(0, 1L);
            ArrayList<Long> fsum = new ArrayList<>();
            long cur = 0;
            for (int i = 0; i < f.size(); i++) {
                cur += f.get(i);
                fsum.add(cur);
            }
            cnt = new long[] { zerosum[len - 1] - 1, onesum[len - 1] };
            boolean[] dig = new boolean[len];
            int prev = len - 1;
            dig[prev--] = true;
            while (prev >= 0) {
                int ind = prev - 1;
                while (ind >= 0 && cnt[0] + fsum.get(ind) * len >= n)
                    ind--;
                if (ind >= 0 && cnt[0] + fsum.get(ind) * len < n) {
                    cnt[0] += fsum.get(ind) * len;
                    cnt[1] += onesum[ind] + fsum.get(ind);
                    dig[ind] = true;
                    ind--;
                }
                prev = ind;
            }
            // cnt[0] -= len;
            // for(int i = 0; i < dig.length; i++){
            // if(dig[i]) cnt[1]--;
            // }
            for (int i = 0; i <= digs; i++) {
                if (dig[len - 1 - i])
                    cnt[1]++;
                cnt[0]++;
            }

            // int ind = 0;
            // int lim = zerosum.length;
            // while(ind + 1 < lim && cnt[1] + zerosum[ind + 1] <= n){
            // ind++;
            // }
            // cnt[1] += zerosum[ind];
            // cnt[0] += onesum[ind];
            // cnt[1] += 0;

        }
        System.out.println(n + " " + cnt[1]);
    }
}