import java.io.*;
import java.util.*;

public class dreams {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int nsongs = Integer.parseInt(tokenizer.nextToken());
        int fav = Integer.parseInt(tokenizer.nextToken()) - 1;
        int[] songs = new int[nsongs];
        tokenizer = new StringTokenizer(in.readLine());
        int tracklen = 0;
        for (int i = 0; i < nsongs; i++) {
            songs[i] = Integer.parseInt(tokenizer.nextToken());
            tracklen += songs[i];
        }
        tracklen -= songs[fav];
        if (tracklen != 0) {
            songs = new int[] { songs[fav], tracklen };
        } else {
            songs = new int[] { songs[fav] };
        }
        tracklen += songs[0];
        int days = Integer.parseInt(in.readLine());
        for (int i = 0; i < days; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int cur = 0;
            int s = 0;
            int ans = 0;
            for (int j = 0; j < n; j++) {
                int t = Integer.parseInt(tokenizer.nextToken());
                if (j % 2 == 0) {
                    cur = 0;
                    s = 0;
                    int times = t / songs[0];
                    int rem = t % songs[0];
                    ans += times * songs[0];
                    ans += Math.min(rem, songs[0]);
                    if(rem == 0){
                        cur++;
                    }
                    else if (rem >= songs[0]) {
                        cur++;
                        s = rem - songs[0];
                    } else {
                        s = rem;
                    }
                    if (cur == songs.length) {
                        cur = 0;
                    }
                } else {
                    int left = songs[cur] - s;
                    while (!(s == 0 && cur == 0) && t > 0) {
                        int t1 = Math.min(songs[cur] - s, t);
                        s += t1;
                        if (cur == 0) {
                            ans += t1;
                        }
                        t -= t1;
                        if (s == songs[cur]) {
                            cur = (cur + 1) % songs.length;
                            s = 0;
                        }
                    }
                    if(s == 0 && cur == 0){
                        int times = t / tracklen;
                        int rem = t % tracklen;
                        ans += times * songs[0];
                        ans += Math.min(rem, songs[0]);
                        if (rem >= songs[0]) {
                            cur++;
                            s = rem - songs[0];
                        } else {
                            s = rem;
                        }
                        if (cur == songs.length) {
                            cur = 0;
                        }
                    }
                }
            }
            System.out.println(ans);
        }
        in.close();
    }
}