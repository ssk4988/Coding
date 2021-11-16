import java.io.*;
import java.util.*;

public class d8p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d8p1.in"));
        ArrayList<Integer> done = new ArrayList<>();
        ArrayList<String> action = new ArrayList<>();
        ArrayList<Integer> numaction = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            action.add(line.split(" ")[0]);
            numaction.add(Integer.parseInt(line.split(" ")[1]));
        }
        for (int i = 0; i < numaction.size(); i++) {
            if (action.get(i).equals("jmp")) {
                action.set(i, "nop");
            } else if (action.get(i).equals("nop")) {
                action.set(i, "jmp");
            }
            //System.out.println(i);
            int index = 0;
            int acc = 0;
            done = new ArrayList<>();
            while (index < action.size() && !done.contains(index)) {
                done.add(index);
                if (action.get(index).equals("acc")) {
                    acc += numaction.get(index);
                    index++;
                }
                else if (action.get(index).equals("jmp")) {
                    index += numaction.get(index);
                }
                else if (action.get(index).equals("nop")) {
                    index++;
                }
            }
            if (index >= action.size()) {
                System.out.println(acc + " " + i);
            }
            if (action.get(i).equals("jmp")) {
                action.set(i, "nop");
            } else if (action.get(i).equals("nop")) {
                action.set(i, "jmp");
            }

        }
        in.close();
    }

}
