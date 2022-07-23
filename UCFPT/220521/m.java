import java.io.*;
import java.util.*;

public class m {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n= Integer.parseInt(in.readLine());
        hw[] hws = new hw[n];
        for(int i = 0; i <n; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            hws[i] = new hw(i, Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
        }
        Arrays.sort(hws);
        long[] bit = new long[n+1];
        for(int i = 0; i < n; i++){
            update(bit, i, hws[i].time);
        }
        for(int i = 0; i < n-1; i++){
            for(int j= n-2; j >= n - 2 - i; j--){
                if(hws[j].id > hws[j+1].id){
                    long left = j == 0 ? 0 : sum(bit, j-1);
                    if(left + hws[j+1].time <= hws[j+1].deadline && left + hws[j+1].time + hws[j].time <= hws[j].deadline){
                        update(bit, j, -hws[j].time);
                        update(bit, j+1, -hws[j+1].time);
                        hw temp = hws[j];
                        hws[j] = hws[j+1];
                        hws[j+1] = temp;
                        update(bit, j, hws[j].time);
                        update(bit, j+1, hws[j+1].time);
                    }
                }
            }
        }
        boolean works = true;
        long tot = 0;
        for(int i = 0; i < n; i++){
            tot += hws[i].time;
            if(tot > hws[i].deadline) works = false;
        }
        if(works){
            StringBuilder b = new StringBuilder();
            for(int i = 0; i <n ;i++){
                b.append((hws[i].id + 1) + (i + 1 < n ? " " : "\n"));
            }
            System.out.print(b);
        }
        else{
            System.out.println("*");
        }
        in.close();
    }
    public static long sum(long[] bit, int index){
        long s = 0;
        index++;
        while(index > 0){
            s += bit[index];
            index -= index & -index;
        }
        return s;
    }
    public static void update(long[] bit, int index, long change){
        index++;
        while(index < bit.length){
            bit[index] += change;
            index += index & -index;
        }
    }
    public static class hw implements Comparable<hw>{
        int id;
        long time;
        long deadline;
        public hw(int id, long time, long deadline){
            this.time = time;
            this.deadline = deadline;
            this.id = id;
        }
        @Override
        public int compareTo(m.hw o) {
            if(this.deadline == o.deadline){
                return this.id - o.id;
            }
            else if(this.deadline < o.deadline) return -1;
            return 1;
        }
    }
}