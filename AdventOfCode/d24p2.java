import java.io.*;
import java.util.*;

public class d24p2 {
    public static Map<String, Boolean> map;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d24p1.in"));

        map = new HashMap<>();
        String line;
        while ((line = in.readLine()) != null) {
            int[] dirs = new int[2];
            for (int i = 0; i < line.length(); i++) {
                String dir = line.substring(i, i + 1);
                if (dir.equals("n") || dir.equals("s")) {
                    i++;
                    dir += line.substring(i, i + 1);
                }
                switch (dir) {
                    case "w":
                        dirs[0] -= 2;
                        break;
                    case "e":
                        dirs[0] += 2;
                        break;
                    case "sw":
                        dirs[0] -= 1;
                        dirs[1] -= 1;
                        break;
                    case "ne":
                        dirs[0] += 1;
                        dirs[1] += 1;
                        break;
                    case "se":
                        dirs[0] += 1;
                        dirs[1] -= 1;
                        break;
                    case "nw":
                        dirs[0] -= 1;
                        dirs[1] += 1;
                        break;
                }
            }
            String key = ArrtoStr(dirs);
            // System.out.println(key);
            if (map.containsKey(key)) {
                map.put(key, !map.get(key));
            } else {
                map.put(key, true);
            }
        }
        int black = 0;
        for (String key : map.keySet()) {
            black += map.get(key) ? 1 : 0;
            // System.out.println(key + " " + map.get(key));
        }

        System.out.println(black);
        int numDays = 101;
        for (int i = 0; i < numDays; i++) {
            Map<String, Boolean> map2 = new HashMap<>();
            ArrayList<String> checked = new ArrayList<>();
            for (String key : map.keySet()) {
                String target = key;
                if (!map2.containsKey(target)) {
                    boolean val = map.get(target);
                    int neighBlack = numBlack(getNeighbors(StrtoArr(target)));
                    if (val) {
                        if (neighBlack == 0 || neighBlack > 2) {
                            map2.put(target, false);
                        } else {
                            map2.put(target, true);
                        }

                    } else {
                        if (neighBlack == 2) {
                            map2.put(target, true);
                        } else {
                            map2.put(target, false);
                        }
                    }
                }
                for (int[] arr : getNeighbors(StrtoArr(key))) {
                    target = ArrtoStr(arr);
                    if (!map2.containsKey(target)) {
                        boolean val = map.containsKey(target) && map.get(target) ? true : false;
                        int neighBlack = numBlack(getNeighbors(StrtoArr(target)));
                        if (val) {
                            if (neighBlack == 0 || neighBlack > 2) {
                                map2.put(target, false);
                            } else {
                                map2.put(target, true);
                            }

                        } else {
                            if (neighBlack == 2) {
                                map2.put(target, true);
                            } else {
                                map2.put(target, false);
                            }
                        }
                    }
                }
            }
            map = map2;
            if ((i + 1) % 10 == 0) {
                black = 0;
                for (String key : map.keySet()) {
                    black += map.get(key) ? 1 : 0;
                    // System.out.println(key + " " + map.get(key));
                }

                System.out.println((i + 1) + " " + black);
            }

        }

        in.close();
    }

    public static String ArrtoStr(int[] arr) {
        return arr[0] + " " + arr[1];
    }

    public static int numBlack(ArrayList<int[]> arr) {
        int count = 0;
        for (int[] neighbor : arr) {
            String str = ArrtoStr(neighbor);
            if (map.containsKey(str) && map.get(str)) {
                count++;
            }
        }
        return count;
    }

    public static int[] StrtoArr(String s) {
        String[] sArr = s.split(" ");
        int[] ret = new int[] { Integer.parseInt(sArr[0]), Integer.parseInt(sArr[1]) };
        return ret;
    }

    public static ArrayList<int[]> getNeighbors(int[] original) {
        ArrayList<int[]> answers = new ArrayList<>();
        answers.add(new int[] { original[0] - 2, original[1] });
        answers.add(new int[] { original[0] + 2, original[1] });
        answers.add(new int[] { original[0] - 1, original[1] - 1 });
        answers.add(new int[] { original[0] + 1, original[1] + 1 });
        answers.add(new int[] { original[0] + 1, original[1] - 1 });
        answers.add(new int[] { original[0] - 1, original[1] + 1 });
        return answers;
    }
}
