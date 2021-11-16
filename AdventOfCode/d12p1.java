import java.io.*;
import java.util.*;

public class d12p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d12p1.in"));

        int xpos = 0;
        int ypos = 0;
        int angle = 90;
        int[] dirx = { 0, 1, 0, -1 };
        int[] diry = { 1, 0, -1, 0 };
        String line;
        while ((line = in.readLine()) != null) {
            String letter = line.substring(0, 1);
            int num = Integer.parseInt(line.substring(1, line.length()));
            int dir = angle;
            if (letter.equals("L")) {
                angle -= num;
            } else if (letter.equals("R")) {
                angle += num;
            } else {
                if (letter.equals("N")) {
                    dir = 0;
                }
                if (letter.equals("E")) {
                    dir = 90;
                }
                if (letter.equals("S")) {
                    dir = 180;
                }
                if (letter.equals("W")) {
                    dir = 270;
                }
                if (letter.equals("F")) {
                    dir = angle;
                }
                //System.out.println(line + " " + angle + " " + dir + " " + Math.floorMod(dir, 360));
                xpos += dirx[Math.floorMod(dir, 360) / 90] * num;
                ypos += diry[Math.floorMod(dir, 360) / 90] * num;
            }
        }
        System.out.println(Math.abs(xpos) + Math.abs(ypos));

        in.close();
    }

}
