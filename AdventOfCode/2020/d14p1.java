import java.io.*;
import java.util.*;

public class d14p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d14p1.in"));
        String currentMask = "";
        String line;
        TreeMap<String, Long> numbas = new TreeMap<>();
        while ((line = in.readLine()) != null) {
            if (!line.subSequence(0, 3).equals("mem")) {
                currentMask = line;
            } else {
                Long newNum = Long.parseLong(line.split(" ")[2]);
                Long placeValue = 1l;
                for (int i = currentMask.length() - 1; i >= 0; i--) {
                    if (currentMask.charAt(i) == 'X') {

                    } else if (currentMask.charAt(i) == '1') {
                        if ((newNum | placeValue) == newNum) {
                        } else {
                            newNum += placeValue;
                        }
                    } else {
                        if ((newNum | placeValue) == newNum) {
                            newNum -= placeValue;
                        } else {

                        }
                    }
                    placeValue *= 2;
                }
                numbas.put(line.split(" ")[0], newNum);
            }
        }
        Long sum = 0l;
        for (String l : numbas.keySet()) {
            sum += numbas.get(l);
        }
        System.out.println(sum);

        in.close();
    }

}
