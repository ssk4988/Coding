import java.io.*;
import java.util.*;

public class d12p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d12p1.in"));

        int xpos = 0;
        int ypos = 0;
        int wx = 10;
        int wy = 1;
        int[] dirx = { 0, 1, 0, -1 };
        int[] diry = { 1, 0, -1, 0 };
        String line;
        while ((line = in.readLine()) != null) {
            String letter = line.substring(0, 1);
            int num = Integer.parseInt(line.substring(1, line.length()));
            if (letter.equals("L")||letter.equals("R")) {
                int factor = 0;
                if(letter.equals("L")) factor -= num;
                else factor += num;
                factor = Math.floorMod(factor, 360) / 90;
                for(int i = 0; i < factor; i++){
                    int tmp = wx;
                    wx = wy;
                    wy = -1 * tmp;
                }
            }
            else if(letter.equals("F")){
                xpos += wx * num;
                ypos += wy * num;
            }
            else {
                int dir = 0;
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
                //System.out.println(line + " " + angle + " " + dir + " " + Math.floorMod(dir, 360));
                wx += dirx[dir / 90] * num;
                wy += diry[dir / 90] * num;
            }
        }
        System.out.println(Math.abs(xpos) + Math.abs(ypos));

        in.close();
    }

}
