
import java.io.*;
import java.util.*;

public class whereami {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("whereami.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("whereami.out")));
        int numFarms = Integer.parseInt(in.readLine());
        String phrase = in.readLine();
        num: for(int i = 1; i <= numFarms; i++){
            for(int j = 0; j + i <= phrase.length(); j++){
                String sig = phrase.substring(j, i + j);
                if(phrase.indexOf(sig, j + 1) != -1){
                    continue num;
                }
            }
            out.println(i);
            break;
        }


        in.close();
        out.close();
    }
}