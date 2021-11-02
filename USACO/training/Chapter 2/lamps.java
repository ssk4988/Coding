/*
ID: ssk49881
LANG: JAVA
TASK: lamps
*/

import java.io.*;
import java.util.*;

public class lamps {
    public static ArrayList<String> buttoncombos = new ArrayList<>();
    public static ArrayList<String> solutions = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("lamps.in"));
        PrintWriter out = new PrintWriter(new File("lamps.out"));
        int numLamps = Integer.parseInt(in.nextLine());
        int numPush = Integer.parseInt(in.nextLine());
        int[] initial = new int[numLamps + 1];
        Arrays.fill(initial, 1);
        int[] finallamps = new int[numLamps + 1];
        Arrays.fill(finallamps, -1);
        String[] phrases = in.nextLine().split(" ");
        ArrayList<Integer> checkIndices = new ArrayList<>();
        for (String phr : phrases) {
            if (Integer.parseInt(phr) == -1) {

            } else {
                finallamps[Integer.parseInt(phr)] = 1;
                checkIndices.add(Integer.parseInt(phr));
            }
        }
        phrases = in.nextLine().split(" ");
        for (String phr : phrases) {
            if (Integer.parseInt(phr) == -1) {

            } else {
                finallamps[Integer.parseInt(phr)] = 0;
                checkIndices.add(Integer.parseInt(phr));
            }
        }
        if (numPush == 0) {
            buttoncombos.add("");
        } else {
            if (numPush <= 2) {
                permute("", numPush);
            } else if (numPush % 2 == 1) {
                permute("", 1);
                permute("", 3);
            } else if (numPush % 2 == 0) {
                permute("", 2);
                permute("", 4);
            }
        }

        for (String pushes : buttoncombos) {
            System.out.println(pushes);
            int[] initialclone = initial.clone();
            for (char chr : pushes.toCharArray()) {
                initialclone = toggle(Integer.parseInt(String.valueOf(chr)), initialclone);
            }
            if (isValid(initialclone, finallamps, checkIndices)) {
                String lamps = "";
                for (int i = 1; i < initialclone.length; i++) {
                    lamps += initialclone[i];
                }
                if (!solutions.contains(lamps)) {
                    solutions.add(lamps);
                }
            }
        }
        Collections.sort(solutions);
        for (String solution : solutions) {
            out.println(solution);
        }
        if (solutions.size() == 0) {
            out.println("IMPOSSIBLE");
        }

        in.close();
        out.close();
    }

    public static void permute(String str, int length) {
        if (length == 0) {
            if (!buttoncombos.contains(str)) {
                buttoncombos.add(str);
            }
            return;
        }

        for (int i = str.length() == 0 ? 1
                : Integer.parseInt(String.valueOf(str.charAt(str.length() - 1))); i <= 4; i++) {
            permute(str + Integer.toString(i), length - 1);
        }
    }

    public static boolean isValid(int[] pushArray, int[] finallamps, ArrayList<Integer> checkIndices) {
        for (int i : checkIndices) {
            if (pushArray[i] != finallamps[i]) {
                return false;
            }
        }
        return true;
    }

    public static int[] toggle(int button, int[] array) {
        for (int i = 0; i < array.length; i++) {
            if (button == 1) {
                array[i] = array[i] == 1 ? 0 : 1;
            } else if (button == 2) {
                if (i % 2 == 1) {
                    array[i] = array[i] == 1 ? 0 : 1;
                }
            } else if (button == 3) {
                if (i % 2 == 0) {
                    array[i] = array[i] == 1 ? 0 : 1;
                }
            } else if (button == 4) {
                if (i % 3 == 1) {
                    array[i] = array[i] == 1 ? 0 : 1;
                }
            }
        }
        return array;
    }
}