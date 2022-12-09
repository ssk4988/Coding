import java.io.*;
import java.util.*;

public class d23p1 {
    public static void main(String[] args) throws Exception {
        String input = "487912365";
        int numMoves = 100;

        ArrayList<Integer> state = new ArrayList<>();
        for (int i = 0; i < input.length(); i++) {
            state.add(Integer.parseInt(input.substring(i, i + 1)));
        }
        int current = 0;
        int min = 1;
        int max = 9;
        

        for (int i = 0; i < numMoves; i++) {
            current = 0;
            List<Integer> move = new ArrayList<>();
            int searchVal = state.get(current) - 1;
            move.addAll(state.subList(1, 4));
            state.removeAll(state.subList(1, 4));
            // System.out.print(current);
            // System.out.print(move);
            // System.out.println(state);
            // System.out.println(min + " " + max);
            // System.out.println(searchVal);
            while (state.indexOf(searchVal) == -1) {
                if (searchVal <= min) {
                    //System.out.println(state);
                    //System.out.println(searchVal);
                    searchVal = max;
                } else {
                    searchVal--;
                }
            }
            // System.out.println(searchVal);
            int insertIndex = (state.indexOf(searchVal) + 1) % state.size();
            if (insertIndex <= current){
                current += move.size();
            }
                
            state.addAll(insertIndex, move);
            current = (current + 1) % state.size();
            move.clear();
            move.addAll(state.subList(0, current));
            state.removeAll(move);
            state.addAll(move);
            //System.out.println(state);
        }
        String answer = "";
        int addIndex = state.indexOf(1);
        for (int i = 1; i < state.size(); i++) {
            answer += state.get((addIndex + i) % state.size());
        }
        System.out.println(answer);

    }

}
