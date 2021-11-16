import java.io.*;
import java.util.*;

public class d6p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d6p1.in"));
        String line;
        int sum = 0;
        while((line = in.readLine()) != null){
            TreeSet<Character> answers = new TreeSet<>();
            for(char c : line.toCharArray()){
                answers.add(c);
            }
            while ((line = in.readLine()) != null && line.length() > 0) {
                TreeSet<Character> answers2 = new TreeSet<>();
                for(char c : line.toCharArray()){
                    answers2.add(c);
                }
                answers.retainAll(answers2);
            }
            sum += answers.size();
        }
        System.out.println(sum);
        in.close();
    }

}
