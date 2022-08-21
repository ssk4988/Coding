package solutions.suburban;
import java.util.*;
import java.io.*;

public class suburban{
    static Scanner[] sampleInput = new Scanner[]{
            new Scanner("5"),
            new Scanner("25"),
            new Scanner("3"),
            new Scanner("2")
    };
    static int[] sampleOutput = new int[]{
            3,
            5,
            -1,
            2
    };
    static int testcase(Scanner in){
        int X = in.nextInt();
        
        // find the first integer b
        // such that b*b >= X
        int b = 0;
        for(; b*b < X; b++);
        
        // create another integer a.
        // a and b will serve as the adjacent and opposite
        // of a right triangle.
        // b will decrease,
        // a will increase.
        // we want to consider only a and b where
        // a*a + b*b = N.
        // we can stop when a > b
        // because by that point, we'd encounter the same
        // set of pythagorean triples.
        int a = 0, minManDist = Integer.MAX_VALUE;
        while(a <= b){
            if(a*a + b*b > X){
                // too high
                // decrease B
                b--;
            }
            else if(a*a + b*b < X){
                // too low
                // increase A
                a++;
            }
            else{
                // this is a pythagorean triple.
                // record its manhattan distance
                minManDist = Math.min(
                        minManDist,
                        a + b
                );
                
                // we can now do either a++ or b--
                a++;
            }
        }
        
        if(minManDist == Integer.MAX_VALUE){
            minManDist = -1;
        }
        return minManDist;
    }
    public static void main(String[] args){
        for(int s = 0; s < 4; s++){
            if(testcase(sampleInput[s]) != sampleOutput[s]){
                System.out.println("Judge solution does not pass samples");
            }
        }
    
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        for(int t = 0; t < T; t++){
            System.out.println(testcase(in));
        }
    }
}