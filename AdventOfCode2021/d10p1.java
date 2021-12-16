import java.io.*;
import java.util.*;

public class d10p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d10p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while((line = in.readLine()) != null){
            input.add(line);
        }
        in.close();
        Map<Character, Integer> m = new HashMap<>();
        m.put('[', -57);
        m.put(']', 57);
        m.put('{', -1197);
        m.put('}', 1197);
        m.put('(', -3);
        m.put(')', 3);
        m.put('<', -25137);
        m.put('>', 25137);
        int score = 0;
        for(String s : input){
            LinkedList<Integer> list = new LinkedList<>();
            for(char c : s.toCharArray()){
                int k = m.get(c);
                if(list.size() > 0 && k + list.getFirst() == 0){
                    list.removeFirst();
                }
                else if(k < 0){
                    list.addFirst(k);
                }
                else{
                    score += k;
                    break;
                }
            }
        }
        System.out.println(score);
    }
}
