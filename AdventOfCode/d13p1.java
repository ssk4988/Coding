import java.io.*;
import java.util.*;

public class d13p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d13p1.in"));

        int time = Integer.parseInt(in.readLine());
        String data = in.readLine();
        String[] data2 = data.split(",");
        ArrayList<Integer> id =  new ArrayList<>();
        for(int i = 0; i < data2.length; i++){
            if(!data2[i].equals("x")){
                id.add(Integer.parseInt(data2[i]));
            }
        }

        int time2 = Integer.MAX_VALUE;
        int busid = -1;
        for(int i = 0; i < id.size(); i++){
            int num = id.get(i);
            int answer = time % num;
            if(answer > 0){
                answer = num - answer;
            }
            if(answer < time2){
                time2 = answer;
                busid = num;
            }
        }
        System.out.println(busid * time2);

        in.close();
    }

}
