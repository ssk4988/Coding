import java.io.*;
import java.util.*;

public class comfortable {
    public static int numCows;
    public static Cow[][] grid = new Cow[3000][3000];
    public static ArrayList<Cow> added = new ArrayList<>();
    public static int numAdded = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        numCows = Integer.parseInt(in.readLine());
        int[] xval = new int[numCows];
        int[] yval = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            xval[i] = Integer.parseInt(tokenizer.nextToken()) + 1000;
            yval[i] = Integer.parseInt(tokenizer.nextToken()) + 1000;
        }
        for (int i = 0; i < numCows; i++) {
            int x = xval[i];
            int y = yval[i];
            ArrayList<Cow> check = new ArrayList<>();
            Cow newcow = new Cow(x, y);
            // System.out.println(!xgrid.containsKey(y) + " " + !added.contains(newcow));
            if (grid[x][y] == null) {
                grid[x][y] = newcow;
                newcow.addNeighbors();
                if (newcow.numNeighbors == 3) {
                    check.add(newcow);
                }
                if (newcow.up != null && newcow.up.numNeighbors == 3) {
                    check.add(newcow.up);
                }
                if (newcow.down != null && newcow.down.numNeighbors == 3) {
                    check.add(newcow.down);
                }
                if (newcow.left != null && newcow.left.numNeighbors == 3) {
                    check.add(newcow.left);
                }
                if (newcow.right != null && newcow.right.numNeighbors == 3) {
                    check.add(newcow.right);
                }
                // System.out.println("neighbors" + newcow.numNeighbors);
            } else {
                numAdded--;
            }
            // System.out.println("Check size: " + check.size());
            while (check.size() > 0) {
                Cow nextcheck = check.remove(0);
                if (nextcheck.numNeighbors != 3) {
                    continue;
                }
                x = nextcheck.x;
                y = nextcheck.y;
                // System.out.println(x + " " + y);
                int addx = -1;
                int addy = -1;
                if (nextcheck.up == null) {
                    addx = 0;
                    addy = 1;
                } else if (nextcheck.down == null) {
                    addx = 0;
                    addy = -1;
                } else if (nextcheck.right == null) {
                    addx = 1;
                    addy = 0;
                } else if (nextcheck.left == null) {
                    addx = -1;
                    addy = 0;
                } else {
                    continue;
                }
                if ((addx == -1 && addy == -1)) {
                    continue;
                }
                newcow = new Cow(x + addx, y + addy);
                if (grid[x + addx][y + addy] == null) {
                    grid[x + addx][y + addy] = newcow;
                } else {
                    System.out.println("mistake");
                }
                newcow.addNeighbors();
                if (newcow.numNeighbors == 3) {
                    check.add(newcow);
                }
                if (newcow.up != null && newcow.up.numNeighbors == 3) {
                    check.add(newcow.up);
                }
                if (newcow.down != null && newcow.down.numNeighbors == 3) {
                    check.add(newcow.down);
                }
                if (newcow.left != null && newcow.left.numNeighbors == 3) {
                    check.add(newcow.left);
                }
                if (newcow.right != null && newcow.right.numNeighbors == 3) {
                    check.add(newcow.right);
                }
                numAdded++;
                // added.add(newcow);
            }
            System.out.println(numAdded);
        }

        in.close();
        // out.close();
    }

    public static class Cow {
        int x;
        int y;
        int numNeighbors = 0;
        Cow up = null;
        Cow down = null;
        Cow left = null;
        Cow right = null;

        public Cow(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null || obj.getClass() != this.getClass())
                return false;

            Cow cow = (Cow) obj;

            // comparing the state of argument with
            // the state of 'this' Object.
            return (cow.x == this.x && cow.y == this.y);
        }

        public void addNeighbors() {
            up = grid[this.x][this.y + 1];
            if (up != null) {
                up.down = this;
                up.numNeighbors++;
                this.numNeighbors++;
            }
            down = grid[this.x][this.y - 1];
            if (down != null) {
                down.up = this;
                down.numNeighbors++;
                this.numNeighbors++;
            }
            left = grid[this.x - 1][this.y];
            if (left != null) {
                left.right = this;
                left.numNeighbors++;
                this.numNeighbors++;
            }
            right = grid[this.x + 1][this.y];
            if (right != null) {
                right.left = this;
                right.numNeighbors++;
                this.numNeighbors++;
            }
        }
    }
}