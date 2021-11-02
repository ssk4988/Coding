import java.io.*;
import java.util.*;

public class word {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("word.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("word.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numWords = Integer.parseInt(tokenizer.nextToken());
        int numCharacters = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        int numCharsinLine = 0;
        while(tokenizer.hasMoreTokens()){
            String word = tokenizer.nextToken();
            if(numCharsinLine == 0){

            }
            else if(numCharsinLine + word.length() <= numCharacters){
                out.print(" ");
            }
            else{
                out.println();
                numCharsinLine = 0;
            }
            out.print(word);
            numCharsinLine += word.length();
        }
        in.close();
        out.close();
    }
}