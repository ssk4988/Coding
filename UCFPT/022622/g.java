import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String input = in.readLine();
        int length = input.length();
        int consW = 0;
        int rank = 25;
        int stars = 0;
        for (int i = 0; i < length; i++) {
            boolean win = input.charAt(i) == 'W';
            if (win) {
                consW++;
                int add = 1;
                if(consW >= 3 && rank <= 25 && rank >= 6){
                    add++;
                }
                stars += add;
                if(stars > starCnt(rank)){
                    stars -= starCnt(rank);
                    rank--;
                    if(rank == 0) break;
                }
            } else {
                consW = 0;
                if(rank >= 1 && rank <= 20){
                    if(!(stars == 0 && rank == 20)){
                        stars--;
                    }
                    if(stars < 0){
                        rank++;
                        stars += starCnt(rank);
                    }
                }
            }

        }
        if(rank == 0){
            System.out.println("Legend");
        }
        else{
            System.out.println(rank);
        }

        in.close();
        out.close();
    }

    public static int starCnt(int rank) {
        if (rank <= 25 && rank >= 21) {
            return 2;
        }
        if (rank <= 20 && rank >= 16) {
            return 3;
        }
        if (rank <= 15 && rank >= 11) {
            return 4;
        }
        return 5;
    }
}