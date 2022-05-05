import java.io.*;
import java.util.*;

public class turkey {
    //public static int score = 0;

    // public static ArrayList<Integer> prevcnt = new ArrayList<>();
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine(), ",");
            int score = 0;
            int currNum = 0;
            ArrayList<Integer> prevcnt = new ArrayList<>();
            while (tokenizer.hasMoreTokens()) {
                String s = tokenizer.nextToken();

                if (currNum == 9) {
                    int v1 = 0;
                    int turnsleft = 2;
                    int turnsused = 0;
                    boolean extraadded = false;
                    while (turnsleft > 0) {
                        if ((s.charAt(turnsused) >= '0' && s.charAt(turnsused) <= '9') || s.charAt(turnsused) == '-') {
                            v1 = s.charAt(turnsused) == '-' ? 0 : s.charAt(turnsused)-'0';
                        } else if (s.charAt(turnsused) == '/') {
                            v1 = 10 - v1;
                            if(!extraadded){
                                extraadded = true;
                                turnsleft++;
                            }
                        } else {
                            v1 = 10;
                            if(!extraadded){
                                extraadded = true;
                                turnsleft++;
                            }
                        }
                        score += v1;
                        if (prevcnt.size() > 0) {
                            for (int i = 0; i < prevcnt.size(); i++) {
                                if (prevcnt.get(i) > 0) {
                                    prevcnt.set(i, prevcnt.get(i) - 1);
                                    score += v1;
                                    if (prevcnt.get(i) == 0) {
                                        prevcnt.remove(i);
                                        i--;
                                    }
                                }
                            }
                        }
                        turnsleft--;
                        turnsused++;
                    }

                } else if ((s.charAt(0) >= '0' && s.charAt(0) <= '9') || s.charAt(0) == '-') {
                    int v1 = s.charAt(0) == '-' ? 0 : s.charAt(0) - '0';
                    if (prevcnt.size() > 0) {
                        for (int i = 0; i < prevcnt.size(); i++) {
                            if (prevcnt.get(i) > 0) {
                                prevcnt.set(i, prevcnt.get(i) - 1);
                                score += v1;
                                if (prevcnt.get(i) == 0) {
                                    prevcnt.remove(i);
                                    i--;
                                }
                            }
                        }
                    }
                    score += v1;
                    int v2 = 0;
                    if ((s.charAt(1) >= '0' && s.charAt(1) <= '9') || s.charAt(1) == '-') {
                        v2 = s.charAt(1) == '-' ? 0 : s.charAt(1) - '0';
                        if (prevcnt.size() > 0) {
                            for (int i = 0; i < prevcnt.size(); i++) {
                                if (prevcnt.get(i) > 0) {
                                    prevcnt.set(i, prevcnt.get(i) - 1);
                                    score += v2;
                                    if (prevcnt.get(i) == 0) {
                                        prevcnt.remove(i);
                                        i--;
                                    }
                                }
                            }
                        }
                    } else if (s.charAt(1) == '/') {
                        v2 = 10 - v1;
                        if (prevcnt.size() > 0) {
                            for (int i = 0; i < prevcnt.size(); i++) {
                                if (prevcnt.get(i) > 0) {
                                    prevcnt.set(i, prevcnt.get(i) - 1);
                                    score += v2;
                                    if (prevcnt.get(i) == 0) {
                                        prevcnt.remove(i);
                                        i--;
                                    }
                                }
                            }
                        }
                        prevcnt.add(1);
                    }
                    score += v2;
                } else if (s.charAt(0) == 'X') {
                    score += 10;
                    if (prevcnt.size() > 0) {
                        for (int i = 0; i < prevcnt.size(); i++) {
                            if (prevcnt.get(i) > 0) {
                                prevcnt.set(i, prevcnt.get(i) - 1);
                                score += 10;
                                if (prevcnt.get(i) == 0) {
                                    prevcnt.remove(i);
                                    i--;
                                }
                            }
                        }
                    }
                    prevcnt.add(2);
                }

                currNum++;
                //b.append(currNum + " " + score + "\n");
            }
            b.append(score + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
    // public static void update(char c, )
}