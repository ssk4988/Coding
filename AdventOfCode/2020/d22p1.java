import java.io.*;
import java.util.*;

public class d22p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d22p1.in"));
        ArrayList<Integer>[] hands = new ArrayList[2];
        for (int i = 0; i < 2; i++) {
            in.readLine();
            hands[i] = new ArrayList<>();
            String line;
            while((line = in.readLine()) != null && line.length() > 0){
                hands[i].add(Integer.parseInt(line));
            }
        }
        int rounds = 0;
        //System.out.println(Arrays.toString(hands));
        while(hands[0].size() * hands[1].size() != 0){
            int c1 = hands[0].remove(0);
            int c2 = hands[1].remove(0);
            if(c1 > c2){
                hands[0].add(c1);
                hands[0].add(c2);
            }
            else{
                hands[1].add(c2);
                hands[1].add(c1);
            }
            rounds++;
        }
        int sum = 0;
        ArrayList<Integer> winner = new ArrayList<>();
        if(hands[0].size() == 0){
            winner = hands[1];
        }else{
            winner = hands[0];
        }
        for(int i = 0; i < winner.size(); i++){
            sum += (i + 1) * winner.get(winner.size() - i - 1);
        }
        System.out.println(sum);
        System.out.println(rounds);

        in.close();
    }

}
