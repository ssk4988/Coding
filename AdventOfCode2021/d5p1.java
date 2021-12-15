import java.io.*;
import java.util.*;

public class d5p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d5p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        long start = System.currentTimeMillis();
        Map<String, Integer> dou = new HashMap<>();
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        int[][] coord = new int[input.size()][7];
        for (int i = 0; i < input.size(); i++) {
            String[] s = input.get(i).split(" -> ");
            coord[i][0] = Integer.parseInt(s[0].split(",")[0]);
            coord[i][1] = Integer.parseInt(s[0].split(",")[1]);
            coord[i][2] = Integer.parseInt(s[1].split(",")[0]);
            coord[i][3] = Integer.parseInt(s[1].split(",")[1]);
            if (coord[i][0] > coord[i][2] || (coord[i][0] == coord[i][2] && coord[i][1] > coord[i][3])) {
                int tmp = coord[i][0];
                coord[i][0] = coord[i][2];
                coord[i][2] = tmp;
                tmp = coord[i][1];
                coord[i][1] = coord[i][3];
                coord[i][3] = tmp;
            } // not actually necessary
            coord[i][4] = Math.max(Math.abs(coord[i][2] - coord[i][0]), Math.abs(coord[i][3] - coord[i][1]));
            coord[i][5] = (coord[i][2] - coord[i][0]) / coord[i][4];
            coord[i][6] = (coord[i][3] - coord[i][1]) / coord[i][4];
            // System.out.println(Arrays.toString(coord[i]));
        }
        Set<String>[] strs = new Set[input.size()];
        for (int i = 0; i < input.size(); i++) {
            if ((Math.abs(coord[i][5]) | Math.abs(coord[i][6])) != 1) // ^ for part 1 instead of |
                continue;
            strs[i] = new HashSet<>();
            for (int k = 0; k <= coord[i][4]; k++) {
                int x = coord[i][0] + coord[i][5] * k;
                int y = coord[i][1] + coord[i][6] * k;
                // System.out.println(i + " " + j + " " + x + " " + y);
                strs[i].add(x + " " + y);
            }
            for (int j = 0; j < i; j++) {
                if ((Math.abs(coord[j][5]) | Math.abs(coord[j][6])) != 1)
                    continue;

                for (String s2 : strs[j]) {
                    if (strs[i].contains(s2)) {
                        if (!dou.containsKey(s2)) {
                            dou.put(s2, 1);
                        } else {
                            dou.put(s2, dou.get(s2) + 1);
                        }
                    }
                }
            }
        }
        System.out.println(input.size());
        System.out.println(dou.size());
        System.out.println(System.currentTimeMillis() - start);

        in.close();
    }

}
