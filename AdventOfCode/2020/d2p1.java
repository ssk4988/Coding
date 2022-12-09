import java.io.*;
import java.util.*;

public class d2p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d2p1.in"));
        ArrayList<Integer> lower = new ArrayList<>();
        ArrayList<Integer> upper = new ArrayList<>();
        ArrayList<String> key = new ArrayList<>();
        ArrayList<String> passwords = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            lower.add(Integer.parseInt(line.split(" ")[0].split("-")[0]));
            upper.add(Integer.parseInt(line.split(" ")[0].split("-")[1]));
            key.add(line.split(" ")[1].split("-")[0].substring(0, 1));
            passwords.add(line.split(" ")[2]);
        }
        int valid = 0;
        for (int i = 0; i < lower.size(); i++) {
            int occurrences = 0;
            int index = 0;
            while (passwords.get(i).indexOf(key.get(i), index) >= 0) {
                occurrences++;
                index = passwords.get(i).indexOf(key.get(i), index) + 1;
            }
            if (i == 0)
                System.out.println(occurrences);
            if (occurrences >= lower.get(i) && occurrences <= upper.get(i))
                valid++;
        }
        System.out.println(valid);
        valid = 0;
        for (int i = 0; i < lower.size(); i++) {
            int occurrences = 0;
            if(passwords.get(i).substring(lower.get(i)-1, lower.get(i)).equals(key.get(i))) occurrences++;
            if(passwords.get(i).substring(upper.get(i)-1, upper.get(i)).equals(key.get(i))) occurrences++;
            if (i == 0)
                System.out.println(occurrences);
            if (occurrences == 1)
                valid++;
        }
        System.out.println(valid);

        in.close();
    }
}
