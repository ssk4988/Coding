import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String[] days = new String[]{"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        String currDay = tokenizer.nextToken();
        int cDay = 0;
        for(int i = 0; i < days.length; i++){
            if(days[i].equals(currDay)){
                cDay = i;
            }
        }
        int[] cycle =new int[7];
        int[] nextDay = new int[]{2, 3, 4, 0, 0, 0, 1};
        int[] len = new int[]{30, 30, 30, 32, 31, 30, 30};
        for(int i = 0; i < cycle.length-2; i++){
            if(i == 1 || i == 3) continue;
            int cur = i;
            cycle[i] += len[i];
            cur = nextDay[i];
            while(cur != i){
                cycle[i] += len[cur];
                cur = nextDay[cur];
            }

        }
        int n = Integer.parseInt(tokenizer.nextToken());
        tokenizer =new StringTokenizer(in.readLine());
        int min = len[cDay];
        for(int i = 0; i < n; i++){
            int d = Integer.parseInt(tokenizer.nextToken());
            int dow = (((cDay - d)% 7)+14)%7;
            int left = d;
            int dow2 = dow;
            while(cycle[dow2] == 0 && left >= len[dow2]){
                left -= len[dow2];
                dow2 = nextDay[dow2];
            }
            if(cycle[dow2] != 0){
                left %= cycle[dow2];
            }
            while(left >0 || (left == 0 && d <= 0)){
                left -= len[dow2];
                dow2 = nextDay[dow2];
            }
            min = Math.min(-left, min);
        }
        System.out.println(min);
        in.close();
    }
}