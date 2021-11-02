
import java.io.*;
import java.util.*;

public class breedflip {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("breedflip.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("breedflip.out")));
        int numChar = Integer.parseInt(in.readLine());
        String a = in.readLine();
        String b = in.readLine();
        boolean[] needsFixing = new boolean[numChar];
        for(int i = 0; i < numChar; i++){
            if(a.charAt(i) == b.charAt(i)){
                needsFixing[i] = false;
            }
            else{
                needsFixing[i] = true;
            }
        }
        int numFlips = 0;
        for(int i = 0; i < numChar; i++){
            if(!needsFixing[i]) continue;
            numFlips++;
            for(int j = i; j < numChar && needsFixing[j]; j++){
                needsFixing[j] = false;
            }
        }
        out.println(numFlips);

        in.close();
        out.close();
    }
}