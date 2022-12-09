import java.io.*;
import java.util.*;

public class d4p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d4p1.in"));
        int numvalid = 0;
        String line;
        while ((line = in.readLine()) != null) {
            ArrayList<String> keys = new ArrayList<>();
            ArrayList<String> values = new ArrayList<>();

            for (String s : line.split(" ")) {
                keys.add(s.split(":")[0]);
                values.add(s.split(":")[1]);
            }
            while ((line = in.readLine()) != null && line.length() > 0) {
                for (String s : line.split(" ")) {
                    keys.add(s.split(":")[0]);
                    values.add(s.split(":")[1]);
                }
            }
            int numReq = 0;
            for (int i = 0; i < keys.size(); i++) {
                String key = keys.get(i);
                String data = values.get(i);
                if (key.equals("byr")) {
                    int value = Integer.parseInt(data);
                    if (value >= 1920 && value <= 2002)
                        numReq++;
                }
                if (key.equals("iyr")) {
                    int value = Integer.parseInt(data);
                    if (value >= 2010 && value <= 2020)
                        numReq++;
                }
                if (key.equals("eyr")) {
                    int value = Integer.parseInt(data);
                    if (value >= 2020 && value <= 2030)
                        numReq++;
                }
                if (key.equals("hgt") && data.length() > 2) {
                    int value = Integer.parseInt(data.substring(0, data.length() - 2));
                    String type = data.substring(data.length() - 2, data.length());
                    if ((type.equals("cm") && value >= 150 && value <= 193)
                            || (type.equals("in") && value >= 59 && value <= 76))
                        numReq++;
                }
                if (key.equals("hcl") && data.length() == 7) {
                    boolean meets = true;
                    for (int j = 1; j < 7; j++) {
                        if (!((data.charAt(j) - '0' <= 9 && data.charAt(j) - '0' >= 0)
                                || (data.charAt(j) - 'a' <= 5 && data.charAt(j) - 'a' >= 0)))
                            meets = false;
                    }
                    if (data.charAt(0) == '#' && meets)
                        numReq++;
                }
                if (key.equals("ecl") && (data.equals("amb") || data.equals("blu") || data.equals("brn")
                        || data.equals("gry") || data.equals("grn") || data.equals("hzl") || data.equals("oth"))) {
                    numReq++;
                }
                if (key.equals("pid") && data.length() == 9) {
                    boolean meets = true;
                    for (int j = 1; j < 7; j++) {
                        if (!(data.charAt(j) - '0' <= 9 && data.charAt(j) - '0' >= 0))
                            meets = false;
                    }
                    if (meets)
                        numReq++;
                }
            }
            if (numReq >= 7)
                numvalid++;
        }
        System.out.println(numvalid);

        in.close();
    }

}
