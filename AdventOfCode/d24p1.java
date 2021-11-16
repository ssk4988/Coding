import java.io.*;
import java.util.*;

public class d24p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d24p1.in"));

        Map<String, Integer> map = new HashMap<>();
        String line;
        while ((line = in.readLine()) != null) {
            double[] dirs = new double[2];
            for (int i = 0; i < line.length(); i++) {
                String dir = line.substring(i, i + 1);
                if (dir.equals("n") || dir.equals("s")) {
                    i++;
                    dir += line.substring(i, i + 1);
                }
                switch (dir) {
                    case "w":
                        dirs[0]-=1.0;
                        break;
                    case "e":
                        dirs[0]+=1.0;
                        break;
                    case "sw":
                        dirs[0] -= 0.5;
                        dirs[1] -= 0.5;
                        break;
                    case "ne":
                        dirs[0] += 0.5;
                        dirs[1] += 0.5;
                        break;
                    case "se":
                        dirs[0] += 0.5;
                        dirs[1] -= 0.5;
                        break;
                    case "nw":
                        dirs[0] -= 0.5;
                        dirs[1] += 0.5;
                        break;
                }
            }
            String key = Arrays.toString(dirs);
            // System.out.println(key);
            if (map.containsKey(key)) {
                map.put(key, 1 - map.get(key));
            } else {
                map.put(key, 1);
            }
        }
        int black = 0;
        for (String key : map.keySet()) {
            black += map.get(key);
        }
        System.out.println(black);

        in.close();
    }

}
