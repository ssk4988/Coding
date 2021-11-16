import java.io.*;
import java.util.*;

public class d16p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d16p1.in"));
        ArrayList<Integer> lower = new ArrayList<>();
        ArrayList<Integer> upper = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null && line.length() > 0) {
            String[] data = line.split(":")[1].split(" ");
            lower.add(Integer.parseInt(data[1].split("-")[0]));
            upper.add(Integer.parseInt(data[1].split("-")[1]));
            lower.add(Integer.parseInt(data[3].split("-")[0]));
            upper.add(Integer.parseInt(data[3].split("-")[1]));
        }
        int size = lower.size() / 2;
        in.readLine();
        String[] myticket = in.readLine().split(",");
        in.readLine();
        in.readLine();
        Set<Integer>[] valid = new Set[size];
        for (int i = 0; i < valid.length; i++) {
            valid[i] = new HashSet<>();
            for (int j = 0; j < size; j++) {
                valid[i].add(j);
            }
        }
        while ((line = in.readLine()) != null) {
            String[] data = line.split(",");
            outer: for (int i = 0; i < size; i++) {
                int m = Integer.parseInt(data[i]);
                int works = 0;
                for (int j = 0; j < size; j++) {
                    if ((m >= lower.get(j * 2) && m <= upper.get(j * 2))
                            || (m >= lower.get(j * 2 + 1) && m <= upper.get(j * 2 + 1))) {
                        works++;
                    }
                }
                if(works == 0) break outer;
                for (int j = 0; j < size; j++) {
                    if ((m >= lower.get(j * 2) && m <= upper.get(j * 2))
                            || (m >= lower.get(j * 2 + 1) && m <= upper.get(j * 2 + 1))) {
                    } else {
                        valid[j].remove(i);
                    }
                }
            }
        }
        int possSum = 0;
        for (int i = 0; i < size; i++) {
            possSum += valid[i].size();
        }
        while(possSum > size){
            for(int i = 0; i < size; i++){
                if(valid[i].size() == 1){
                    for(int j = 0; j < size; j++){
                        if(i == j) continue;
                        valid[j].removeAll(valid[i]);
                    }
                }
            }
            possSum = 0;
            for (int i = 0; i < size; i++) {
                possSum += valid[i].size();
            }
        }
        long prod = 1;
        for(int i = 0; i < 6; i++){
            prod *= Integer.parseInt(myticket[valid[i].iterator().next()]);
        }
        System.out.println(prod);

        in.close();
    }

}
