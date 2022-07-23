import java.io.*;
import java.util.*;

public class rook {
    public static piece rook;    
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("./data/rook/rook.in"));
        PrintWriter out = new PrintWriter(new FileWriter("./rook.out"));
        int numCases = Integer.parseInt(in.readLine());
        long start_time = System.currentTimeMillis();
        for (int caseNum = 0; caseNum < numCases; caseNum++) {
            int numPieces = Integer.parseInt(in.readLine());
            int numPawns = numPieces;
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            ArrayList<TreeSet<piece>> grid = new ArrayList<>();
            grid.add(new TreeSet<>());
            rook = new piece(Integer.parseInt(tokenizer.nextToken()), 0, 0);
            piece[] pawns = new piece[numPieces];
            for (int i = 0; i < numPieces; i++) {
                pawns[i] = new piece(Integer.parseInt(tokenizer.nextToken()), 0, i + 1);
                grid.get(0).add(pawns[i]);
            }
            grid.get(0).add(rook);
            for (piece p : grid.get(0)) {
                piece higher = grid.get(0).higher(p);
                if (higher != null) {
                    p.right = higher;
                    higher.left = p;
                }
            }
            // Collections.sort(grid.get(0));
            ArrayList<piece> theList = new ArrayList<>();

            while (numPawns > 1) {
                // int rookindex = Collections.binarySearch(grid.get(0), rook);
                piece closest = closest(rook);
                if (closest == null) {
                    int newRow;
                    for (newRow = rook.y + 1; newRow < grid.size(); newRow++) {
                        if (grid.get(newRow).size() > 0)
                            break;
                    }
                    insert(grid, newRow, rook);
                } else {
                    theList.add(closest);
                    grid.get(closest.y).remove(closest);
                    if (closest == rook.left) {
                        piece leftleft = rook.left.left;
                        if (leftleft != null) {
                            leftleft.right = rook;
                            rook.left = leftleft;
                        } else {
                            rook.left = null;
                        }
                    } else {
                        piece rightright = rook.right.right;
                        if (rightright != null) {
                            rightright.left = rook;
                            rook.right = rightright;
                        } else {
                            rook.right = null;
                        }
                    }
                    rook.x = closest.x;
                    closest.left = null;
                    closest.right = null;
                    numPawns--;
                }
                closest = closest(rook);
                if (closest != null) {
                    if (grid.size() - 1 == closest.y) {
                        grid.add(new TreeSet<>());
                    }
                    //System.out.println(closest.y + " " + rook.y + " " + numPawns);
                    insert(grid, closest.y+1, closest);
                }

                // System.out.println("Case " + caseNum + ": " + numPawns);
                // numPawns = 1;
            }
            StringBuilder b = new StringBuilder();
            for (int i = 0; i < theList.size(); i++) {
                b.append(theList.get(i).id + (i < theList.size() - 1 ? " " : "\n"));
            }
            out.print(b);
            System.out.println(b);
        }

        System.out.println(System.currentTimeMillis() - start_time);
        in.close();
        out.close();
    }

    public static void insert(ArrayList<TreeSet<piece>> grid, int row, piece p) {
        if(row >= grid.size()){
            System.out.print("");
        }
        grid.get(p.y).remove(p);
        grid.get(row).add(p);
        p.y = row;
        if(p.right == rook && p.left == rook){
            System.out.println("i hate logic");
        }
        if (p.right != null) {
            p.right.left = p.left;
        }
        if (p.left != null) {
            p.left.right = p.right;
        }
        piece right = grid.get(row).higher(p);
        piece left = grid.get(row).lower(p);
        if (right != null) {
            p.right = right;
            right.left = p;
        }
        if (left != null) {
            p.left = left;
            left.right = p;
        }
    }

    public static piece closest(piece p) {
        piece closest = null;
        piece right = p.right;
        if (right != null) {
            closest = right;
        }
        piece left = p.left;
        if (left != null && (closest == null || p.x - left.x <= closest.x - p.x)) {
            closest = left;
        }
        if(closest == rook){
            System.out.println("bruh moment");
        }
        return closest;
    }

    public static class piece implements Comparable<piece> {
        int x, y, id;
        piece right;
        piece left;

        public piece(int x, int y, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
        }

        @Override
        public int compareTo(rook.piece o) {
            return this.x - o.x;
        }
    }
}