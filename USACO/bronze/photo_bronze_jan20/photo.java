
import java.io.*;
import java.util.*;

public class photo {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("photo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("photo.out")));
        int sequencelength = Integer.parseInt(in.readLine());
        ArrayList<Integer> bseries = new ArrayList<>();
        ArrayList<Integer> aseries = new ArrayList<>();
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        while(tokenizer.hasMoreTokens()){
            bseries.add(Integer.parseInt(tokenizer.nextToken()));
        }
        outer: for(int i2 = 1; i2 < bseries.get(0); i2++){
            aseries = new ArrayList<>();
            aseries.add(i2);
            aseries.add(bseries.get(0) - i2);
            
            for(int i = 1; i < bseries.size(); i++){
                if(aseries.get(i) >= bseries.get(i) || aseries.contains(bseries.get(i) - aseries.get(i))) continue outer;
                aseries.add(bseries.get(i) - aseries.get(i));
            }
            break;
        }
        out.print(aseries.get(0));
        for(int i = 1; i < aseries.size(); i++){
            out.print(" " + aseries.get(i));
        }
        out.println();
        in.close();
        out.close();
    }
}