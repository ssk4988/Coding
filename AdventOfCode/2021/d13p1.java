import java.io.*;
import java.util.*;

public class d13p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d13p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        int numPoints = 0;
        while ((line = in.readLine()) != null) {
            input.add(line);
            if (line.length() == 0) {
                numPoints = input.size() - 1;
            }
        }
        int numTrans = input.size() - 1 - numPoints;
        int[] trans = new int[numTrans];
        for (int i = numPoints + 1; i < input.size(); i++) {
            String s = input.get(i).split(" ")[2];
            trans[i - numPoints - 1] = (s.charAt(0) == 'x' ? 1 : -1) * Integer.parseInt(s.substring(2));
        }
        Set<String> set = new HashSet<>();
        int maxX = 0;
        int maxY = 0;
        for (int i = 0; i < numPoints; i++) {
            int x = Integer.parseInt(input.get(i).split(",")[0]);
            int y = Integer.parseInt(input.get(i).split(",")[1]);
            // System.out.println(x + " " + y);
            for (int j = 0; j < numTrans; j++) {
                // System.out.println(trans[j]);
                if (trans[j] >= 0 && x >= trans[j]) {
                    x -= 2 * (x-trans[j]);
                } 
                if(trans[j] < 0 && y >= -1 * trans[j]) {
                    y -= 2 * (y+trans[j]);
                }
                // System.out.println(x + " " + y);
            }
            maxX = Math.max(x, maxX);
            maxY = Math.max(y, maxY);
            set.add(x + "," + y);
        }
        System.out.println(set.size());
        for(int i = 0; i <= maxY; i++){
            for(int j = 0; j <= maxX; j++){
                System.out.print(set.contains(j + "," + i) ? '#' : '.');
            }
            System.out.println();
        }
        for (String s : set) {
            //System.out.println(s);
        }

        in.close();
    }

}
