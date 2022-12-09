import java.io.*;
import java.util.*;

public class d1p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d1p1.in"));
        String line;
        ArrayList<Integer> list = new ArrayList<>();
        while((line = in.readLine())!= null){
            list.add(Integer.parseInt(line));
        }
        int increased = 0;
        for(int i = 3; i < list.size(); i++){
            if(list.get(i) - list.get(i-3) > 0){
                increased++;
            }
        }
        System.out.println(increased);
        in.close();
    }

}
