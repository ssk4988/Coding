import java.io.*;
import java.util.*;

public class d16p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d16p1.in"));
        ArrayList<Integer> lower = new ArrayList<>();
        ArrayList<Integer> upper = new ArrayList<>();
        String line;
        while((line = in.readLine()) != null && line.length() > 0){
            String[] data = line.split(":")[1].split(" ");
            lower.add(Integer.parseInt(data[1].split("-")[0]));
            upper.add(Integer.parseInt(data[1].split("-")[1]));
            lower.add(Integer.parseInt(data[3].split("-")[0]));
            upper.add(Integer.parseInt(data[3].split("-")[1]));
        }
        for(int i = 0; i < 4; i++){
            in.readLine();
        }
        int output = 0;
        while((line = in.readLine()) != null){
            String[] data = line.split(",");
            for(String l : data){
                int l2 = Integer.parseInt(l);
                int works = 0;
                for(int i = 0; i < lower.size(); i++){
                    if(l2 >= lower.get(i) && l2 <= upper.get(i)){
                        works++;
                        break;
                    }
                }
                if(works == 0){
                    output += l2;
                }
            }
        }
        System.out.println(output);

        in.close();
    }

}
