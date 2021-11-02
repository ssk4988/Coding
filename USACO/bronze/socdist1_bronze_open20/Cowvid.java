import java.util.*;
import java.io.*;

public class Cowvid {
    public static void main(String[] args) throws Exception {
        Scanner scnr = new Scanner(new File("socdist1.in"));
        PrintWriter out = new PrintWriter(new FileWriter("socdist1.out"));
        solve(scnr, out);
        //for (int i = 1; i <= 15; i++) {
        //    Scanner inFile = new Scanner(new File("./" + Integer.toString(i) + ".in"));
        //    Scanner inTest = new Scanner(new File("./" + Integer.toString(i) + ".out"));
        //    System.out.print(Integer.toString(i) + " try:");
        //    test(inFile, inTest);
        //}
    }

    public static void solve(Scanner in, PrintWriter test) throws Exception {
        int n = Integer.parseInt(in.nextLine());
        String cows = in.nextLine();
        char[] newcows = cows.toCharArray();
        int d1length = 0;
        int d2length = 0;
        int d1start = -1;
        int d2start = -1;
        int d1end = -1;
        int d2end = -1;
        boolean d1front = false;
        boolean d2front = false;
        boolean d1back = false;
        boolean d2back = false;
        int currentD = 0;
        int initialD = 10000000;
        boolean seenone = false;
        boolean seenone2 = false;

        for (int i = 0; i < cows.length(); i++) {
            if (cows.charAt(i) == '0') {
                currentD++;
                if (i == cows.length() - 1) {
                    if (currentD > d1length) {
                        d2length = d1length;
                        d2start = d1start;
                        d2end = d1end;
                        d2front = d1front;
                        d2back = d1back;
                        d1length = currentD;
                        d1start = i + 1 - currentD;
                        d1end = i;
                        d1front = d1start != 0 ? true : false;
                        d1back = false;
                    } else if (currentD >= d2length) {
                        d2length = currentD;
                        d2start = i + 1 - currentD;
                        d2end = i;
                        d2front = d2start != 0 ? true : false;
                        d2back = false;
                    }
                }
            } else if (cows.charAt(i) == '1') {
                if (currentD > d1length) {
                    d2length = d1length;
                    d2start = d1start;
                    d2end = d1end;
                    d2front = d1front;
                    d2back = d1back;
                    d1length = currentD;
                    d1start = i - currentD;
                    d1end = i - 1;
                    d1front = d1start != 0 ? true : false;
                    d1back = true;
                } else if (currentD >= d2length) {
                    d2length = currentD;
                    d2start = i - currentD;
                    d2end = i - 1;
                    d2front = d2start != 0 ? true : false;
                    d2back = true;
                }
                if (seenone && currentD < initialD) {
                    initialD = currentD;
                }
                seenone = true;
                currentD = 0;
            }
        }
        if (d1start == -1 && d2start == -1) {
            newcows[0] = '1';
            newcows[newcows.length - 1] = '1';
        } else if (d2start == -1 && d1start != -1) {
            if (d1front && d1back) {
                newcows[d1start + d1length / 3] = '1';
                newcows[d1start + 2 * d1length / 3] = '1';
            } else if (!d1front && !d1back) {
                newcows[d1start] = '1';
                newcows[d1end] = '1';
            } else if (d1front && !d1back) {
                newcows[d1start + d1length / 2 - 1] = '1';
                newcows[d1end] = '1';
            } else if (!d1front && d1back) {
                newcows[d1start] = '1';
                newcows[d1start + d1length / 2] = '1';
            }
        } else if (d1length != 0 && d1start != -1) {
            if (d1front && d1back) {
                newcows[d1start + d1length / 2] = '1';
            } else if (!d1front) {
                newcows[d1start] = '1';
            } else if (!d1back) {
                newcows[d1end] = '1';
            }
        } else if (d2length != 0 && d2start != -1) {
            if (d2front && d2back) {
                newcows[d2start + d2length / 2] = '1';
            } else if (!d2front) {
                newcows[d2start] = '1';
            } else if (!d2back) {
                newcows[d2end] = '1';
            }
        }
        int afterD = 10000000;
        currentD = 0;
        for (int i = 0; i < newcows.length; i++) {
            if (seenone2 && newcows[i] == '0') {
                currentD++;
            } else if (newcows[i] == '1') {
                if (seenone2 && afterD > currentD) {
                    afterD = currentD;
                }
                seenone2 = true;
                currentD = 0;
            }
        }
        afterD++;
        test.write(Integer.toString(afterD));
        in.close();
        test.close();
    }

    public static void test(Scanner in, Scanner test) throws Exception {
        int n = Integer.parseInt(in.nextLine());
        String cows = in.nextLine();
        char[] newcows = cows.toCharArray();
        String actualD = test.nextLine();
        int d1length = 0;
        int d2length = 0;
        int d1start = -1;
        int d2start = -1;
        int d1end = -1;
        int d2end = -1;
        boolean d1front = false;
        boolean d2front = false;
        boolean d1back = false;
        boolean d2back = false;
        int currentD = 0;
        int initialD = 10000000;
        boolean seenone = false;
        boolean seenone2 = false;

        System.out.print(" " + Integer.toString(n) + " numbers: ");

        for (int i = 0; i < cows.length(); i++) {
            if (cows.charAt(i) == '0') {
                currentD++;
                if (i == cows.length() - 1) {
                    if (currentD > d1length) {
                        d2length = d1length;
                        d2start = d1start;
                        d2end = d1end;
                        d2front = d1front;
                        d2back = d1back;
                        d1length = currentD;
                        d1start = i + 1 - currentD;
                        d1end = i;
                        d1front = d1start != 0 ? true : false;
                        d1back = false;
                    } else if (currentD >= d2length) {
                        d2length = currentD;
                        d2start = i + 1 - currentD;
                        d2end = i;
                        d2front = d2start != 0 ? true : false;
                        d2back = false;
                    }
                }
            } else if (cows.charAt(i) == '1') {
                if (currentD > d1length) {
                    d2length = d1length;
                    d2start = d1start;
                    d2end = d1end;
                    d2front = d1front;
                    d2back = d1back;
                    d1length = currentD;
                    d1start = i - currentD;
                    d1end = i - 1;
                    d1front = d1start != 0 ? true : false;
                    d1back = true;
                } else if (currentD >= d2length) {
                    d2length = currentD;
                    d2start = i - currentD;
                    d2end = i - 1;
                    d2front = d2start != 0 ? true : false;
                    d2back = true;
                }
                if (seenone && currentD < initialD) {
                    initialD = currentD;
                }
                seenone = true;
                currentD = 0;
            }
        }
        if (d1start == -1 && d2start == -1) {
            newcows[0] = '1';
            newcows[newcows.length - 1] = '1';
        } else if (d2start == -1 && d1start != -1) {
            if (d1front && d1back) {
                newcows[d1start + d1length / 3] = '1';
                newcows[d1start + 2 * d1length / 3] = '1';
            } else if (!d1front && !d1back) {
                newcows[d1start] = '1';
                newcows[d1end] = '1';
            } else if (d1front && !d1back) {
                newcows[d1start + d1length / 2 - 1] = '1';
                newcows[d1end] = '1';
            } else if (!d1front && d1back) {
                newcows[d1start] = '1';
                newcows[d1start + d1length / 2] = '1';
            }
        } else if (d1length != 0 && d1start != -1) {
            if (d1front && d1back) {
                newcows[d1start + d1length / 2] = '1';
            } else if (!d1front) {
                newcows[d1start] = '1';
            } else if (!d1back) {
                newcows[d1end] = '1';
            }
        } else if (d2length != 0 && d2start != -1) {
            if (d2front && d2back) {
                newcows[d2start + d2length / 2] = '1';
            } else if (!d2front) {
                newcows[d2start] = '1';
            } else if (!d2back) {
                newcows[d2end] = '1';
            }
        }
        int afterD = 10000000;
        currentD = 0;
        for (int i = 0; i < newcows.length; i++) {
            if (seenone2 && newcows[i] == '0') {
                currentD++;
            } else if (newcows[i] == '1') {
                if (seenone2 && afterD > currentD) {
                    afterD = currentD;
                }
                seenone2 = true;
                currentD = 0;
            }
        }
        afterD++;
        System.out.println("Predicted: " + Integer.toString(afterD) + " Actual: " + actualD);

        if (n < 20) {
            System.out.println(" " + cows + " " + String.valueOf(newcows));
        }
        in.close();
        test.close();
    }
}