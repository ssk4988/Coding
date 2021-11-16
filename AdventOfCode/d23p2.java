import java.io.*;
import java.util.*;

public class d23p2 {
    public static void main(String[] args) throws Exception {
        String input = "487912365";
        int numMoves = 10000;
        long start = System.currentTimeMillis();

        ArrayList<Integer> state = new ArrayList<>();
        for (int i = 0; i < input.length(); i++) {
            state.add(Integer.parseInt(input.substring(i, i + 1)));
        }
        int current = 0;
        int min = 1;
        int max = 100;
        for(int i = 10; i <= max; i++){
            state.add(i);
        }
        System.out.println("done adding" + (System.currentTimeMillis() - start));

        ArrayList<String> past = new ArrayList<>();
        int startNum = 0;
        int cycleNum = 0;

        for (int i = 0; i < numMoves; i++) {
            if(past.contains(state.toString())){
                System.out.println(i);
                startNum = past.indexOf(state.toString());
                cycleNum = i;
                break;
            }
            past.add(state.toString());
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
        int cycleLen = cycleNum - startNum;
        System.out.println(startNum + " " + cycleNum + " " + cycleLen);
        int x = numMoves - startNum;
        x = x % cycleLen;
        System.out.println(past.get(x + startNum));
    }

}
