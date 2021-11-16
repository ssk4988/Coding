import java.io.*;
import java.util.*;

public class d17p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d17p1.in"));

        Map<String, Boolean> states = new HashMap<>();

        int initwidth = 0;
        String line;
        int i1 = 0;
        while ((line = in.readLine()) != null) {
            initwidth = line.length();
            for (int j1 = 0; j1 < initwidth; j1++) {
                states.put(i1 + " " + j1 + " " + 0 + " " + 0, line.charAt(j1) == '.' ? false : true);
            }
            i1++;
        }
        int[][] dims = new int[4][2];
        dims[0][0] = 0;
        dims[0][1] = initwidth - 1;
        dims[1][0] = 0;
        dims[1][1] = initwidth - 1;
        dims[2][0] = 0;
        dims[2][1] = 0;
        dims[3][0] = 0;
        dims[3][1] = 0;

        for (int a = 0; a < 6; a++) {
            // System.out.println(a);
            // System.out.println(dims[0][0] + " " + dims[0][1]);
            // System.out.println(dims[1][0] + " " + dims[1][1]);
            // System.out.println(dims[2][0] + " " + dims[2][1]);

            Map<String, Boolean> newStates = new HashMap<>();
            for (int i = 0; i < dims.length; i++) {
                for (int j = 0; j < dims[i].length; j++) {
                    if (j == 0)
                        dims[i][j]--;
                    else
                        dims[i][j]++;
                }
            }
            int[][] newdims = new int[4][2];
            newdims[0][0] = Integer.MAX_VALUE;
            newdims[0][1] = Integer.MIN_VALUE;
            newdims[1][0] = Integer.MAX_VALUE;
            newdims[1][1] = Integer.MIN_VALUE;
            newdims[2][0] = Integer.MAX_VALUE;
            newdims[2][1] = Integer.MIN_VALUE;
            newdims[3][0] = Integer.MAX_VALUE;
            newdims[3][1] = Integer.MIN_VALUE;

            for (int x = dims[0][0]; x <= dims[0][1]; x++) {
                for (int y = dims[1][0]; y <= dims[1][1]; y++) {
                    for (int z = dims[2][0]; z <= dims[2][1]; z++) {
                        for (int w = dims[3][0]; w <= dims[3][1]; w++) {
                            int numActive = 0;
                            for (int x1 = -1; x1 < 2; x1++) {
                                for (int y1 = -1; y1 < 2; y1++) {
                                    for (int z1 = -1; z1 < 2; z1++) {
                                        for (int w1 = -1; w1 < 2; w1++) {
                                            if (x1 == 0 && y1 == 0 && z1 == 0 && w1 == 0)
                                                continue;
                                            String k = (x + x1) + " " + (y + y1) + " " + (z + z1) + " " + (w + w1);
                                            if (states.containsKey(k) && states.get(k)) {
                                                numActive++;
                                            }
                                        }

                                    }
                                }
                            }
                            String k = x + " " + y + " " + z + " " + w;
                            boolean active = states.containsKey(k) && states.get(k);
                            if (active) {
                                if (numActive == 2 || numActive == 3) {
                                    newStates.put(k, true);
                                } else {
                                    newStates.put(k, false);
                                }
                            } else {
                                if (numActive == 3) {
                                    newStates.put(k, true);
                                } else {
                                    newStates.put(k, false);
                                }
                            }
                            if (newStates.get(k)) {
                                if (x < newdims[0][0])
                                    newdims[0][0] = x;
                                if (y < newdims[1][0])
                                    newdims[1][0] = y;
                                if (z < newdims[2][0])
                                    newdims[2][0] = z;
                                if (w < newdims[3][0])
                                    newdims[3][0] = w;
                                if (x > newdims[0][1])
                                    newdims[0][1] = x;
                                if (y > newdims[1][1])
                                    newdims[1][1] = y;
                                if (z > newdims[2][1])
                                    newdims[2][1] = z;
                                if (w > newdims[3][1])
                                    newdims[3][1] = w;
                            }
                        }
                    }
                }
            }
            dims = newdims;
            states = newStates;
        }
        int numActive = 0;
        for (boolean k : states.values()) {
            if (k) {
                numActive++;
            }
        }
        System.out.println(numActive);

        in.close();
    }

}
