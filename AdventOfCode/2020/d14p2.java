import java.io.*;
import java.util.*;

public class d14p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d14p1.in"));
        String currentMask = "";
        String line;
        TreeMap<Long, Long> numbas = new TreeMap<>();
        while ((line = in.readLine()) != null) {
            if (!line.subSequence(0, 3).equals("mem")) {
                currentMask = line;
            } else {
                Long num = Long.parseLong(line.split(" ")[2]);
                Long newAddress = Long.parseLong(line.substring(4).split("]")[0]);
                ArrayList<Long> addresses = new ArrayList<>();
                Long placeValue = 1l;
                for (int i = currentMask.length() - 1; i >= 0; i--) {
                    if (currentMask.charAt(i) == '1') {
                        if ((newAddress | placeValue) == newAddress) {
                        } else {
                            newAddress += placeValue;
                        }
                    }
                    placeValue *= 2;
                }
                addresses.add(newAddress);
                placeValue = 1l;
                for (int i = currentMask.length() - 1; i >= 0; i--) {
                    if (currentMask.charAt(i) == 'X') {
                        ArrayList<Long> newAddresses = new ArrayList<>();
                        for (Long a : addresses) {
                            newAddresses.add(a);
                            if ((a | placeValue) == a) {
                                newAddresses.add(a - placeValue);
                            } else {
                                newAddresses.add(a + placeValue);
                            }
                        }
                        addresses = newAddresses;
                    }
                    placeValue *= 2;
                }
                for(Long l : addresses){
                   numbas.put(l, num); 
                }
                
            }
        }
        Long sum = 0l;
        for (Long l : numbas.keySet()) {
            sum += numbas.get(l);
        }
        System.out.println(sum);

        in.close();
    }

}
