import java.io.*;
import java.util.*;

public class d22p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d22p1.in"));
        ArrayList<Integer>[] hands = new ArrayList[2];
        for (int i = 0; i < 2; i++) {
            in.readLine();
            hands[i] = new ArrayList<>();
            String line;
            while ((line = in.readLine()) != null && line.length() > 0) {
                hands[i].add(Integer.parseInt(line));
            }
        }
        hands = game(hands);
        //System.out.println(Arrays.toString(hands));
        ArrayList<Integer> winner = new ArrayList<>();
        if (hands[0].size() == 0) {
            winner = hands[1];
        } else {
            winner = hands[0];
        }
        int sum = 0;
        for (int i = 0; i < winner.size(); i++) {
            sum += (i + 1) * winner.get(winner.size() - i - 1);
        }
        System.out.println(sum);

        in.close();
    }

    public static ArrayList<Integer>[] game(ArrayList<Integer>[] hands) {
        ArrayList<String> prevHands = new ArrayList<>();
        while (hands[0].size() * hands[1].size() != 0) {
            String tString = Arrays.toString(hands);
            if (prevHands.contains(tString)) {
                hands[1] = new ArrayList<>();
                return hands;
            } else {
                prevHands.add(tString);
                int c1 = hands[0].remove(0);
                int c2 = hands[1].remove(0);
                int winner = -1;
                if (hands[0].size() >= c1 && hands[1].size() >= c2) {
                    ArrayList<Integer>[] subgamehands = new ArrayList[2];
                    subgamehands[0] = new ArrayList<>();
                    subgamehands[1] = new ArrayList<>();
                    for (int i = 0; i < c1; i++) {
                        subgamehands[0].add(hands[0].get(i));
                    }
                    for (int i = 0; i < c2; i++) {
                        subgamehands[1].add(hands[1].get(i));
                    }
                    ArrayList<Integer>[] future = game(subgamehands);
                    if (future[0].size() == 0) {
                        winner = 1;
                    } else {
                        winner = 0;
                    }
                } else {
                    if (c1 > c2) {
                        winner = 0;
                    } else {
                        winner = 1;
                    }
                }
                if (winner == 0) {
                    hands[0].add(c1);
                    hands[0].add(c2);
                } else {
                    hands[1].add(c2);
                    hands[1].add(c1);
                }
            }
        }
        return hands;
    }
}
