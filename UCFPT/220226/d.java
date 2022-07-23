import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int d = Integer.parseInt(in.readLine());
        ArrayList<Long> cost = new ArrayList<>();
        for(int i = 0; i < d; i++){
            long val = Integer.parseInt(in.readLine());
            if(cost.size() == 0 || cost.get(cost.size() - 1) - val != 0){
                cost.add(val);
            }
        }
        //boolean[] min = new boolean[d];
        //boolean[] max = new boolean[d];
        long currowned = 0;
        long balance = 100;
        for(int i = 0; i < cost.size(); i++){
            boolean ismax = true;
            boolean ismin = true;
            if(i > 0){
                if(cost.get(i)>cost.get(i-1)){
                    ismin = false;
                }
                if(cost.get(i) < cost.get(i-1)) {
                    ismax = false;
                }
            }
            if(i+1 < cost.size()){
                if(cost.get(i)>cost.get(i+1)){
                    ismin = false;
                }
                if(cost.get(i) < cost.get(i+1)){
                    ismax = false;
                }
            }
            //min[i] = ismin;
            //max[i] = ismax;
            //System.out.println(ismin + " " + ismax);
            if(ismin && i + 1 < cost.size()){
                long numtobuy = Math.min(100000 - currowned, balance / cost.get(i));
                currowned += numtobuy;
                balance -= numtobuy * cost.get(i);
            }
            if(ismax){
                long numtosell = currowned;
                currowned -= numtosell;
                balance += numtosell * cost.get(i);
            }
        }
        System.out.println(balance);

        in.close();
        out.close();
    }
}