package solutions.rook;

import java.util.*;

public class rook {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int t = s.nextInt();
        for(int tn = 0; tn < t; tn++){
            TreeSet<Long> rookRow = new TreeSet<>();
            TreeSet<Long> belowRook = new TreeSet<>();
            HashMap<Long, Integer> idx = new HashMap<>();

            int n = s.nextInt();
            long rookPos = s.nextInt();
            for(int i = 0; i < n; i++) {
                long x = s.nextInt();
                rookRow.add(x);
                idx.put(x, i+1);
            }

            // System.out.println(rookRow+","+tn+","+n);
            // System.out.flush();
            
            int turn = 1; // 1 for white, 0 for black
            while(rookRow.size() + belowRook.size() > 1){
                if(turn == 0){
                    if(rookRow.size() != 0){
                        // There is a pawn on the rook's row
                        Long left = rookRow.floor(rookPos);
                        Long right = rookRow.ceiling(rookPos);
                        long closest = -1;
                        if(left == null) closest = right;
                        if(right == null) closest = left;
                        if(left != null && right != null){
                            if(rookPos - left <= right - rookPos){
                                closest = left;
                            }else{
                                closest = right;
                            }
                        }
                        rookRow.remove(closest);
                        belowRook.add(closest);
                        // System.out.println("Move "+ idx.get(closest) + "," + closest);
                    }
                }else{
                    if(rookRow.size() == 0){
                        // There are no pawns on the rook's row, so move him down 
                        rookRow = belowRook;
                        belowRook = new TreeSet<>();
                        // System.out.println("advance");
                    }else{
                        Long left = rookRow.floor(rookPos);
                        Long right = rookRow.ceiling(rookPos);
                        long closest = -1;
                        if(left == null) closest = right;
                        if(right == null) closest = left;
                        if(left != null && right != null){
                            if(rookPos - left <= right - rookPos){
                                closest = left;
                            }else{
                                closest = right;
                            }
                        }
                        rookRow.remove(closest);
                        rookPos = closest;
                        // System.out.println("Takes " + idx.get(closest) + "," + closest);
                        System.out.print(idx.get(closest)+" ");
                    }
                }
                turn = (turn+1)%2;
            }
            System.out.println();

        }
        s.close();
    }    
}
