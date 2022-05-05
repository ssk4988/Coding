import java.util.*;
import java.io.*;

public class count {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();

        int testCases = Integer.parseInt(in.readLine());
        for (int testCase = 0; testCase < testCases; testCase ++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numpeople = Integer.parseInt(tokenizer.nextToken());
            int numwords = Integer.parseInt(tokenizer.nextToken());
            

            for (int startPos = 1; startPos <= numpeople; startPos ++) {
                ArrayList<Integer> people = new ArrayList<>();
                for (int i = startPos; i <= numpeople + startPos; i ++) {
                    people.add(i % numpeople);
                }
                
                while (true) {
                    people.remove((numwords - 1) % people.size());
                    if(people.size() == 1) {
                        if (people.get(0) == 1) {
                            b.append(startPos + "\n");
                        }
                        break;
                    }
                }



            }
        }
        
        System.out.print(b);
        in.close();
    }
}