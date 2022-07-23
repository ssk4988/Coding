package solutions.north;

// North
// Java Solution
// Josh Delgado

import java.util.*;

public class north {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    // Create an easy to access way to get the different directions.
    HashMap<Character, Double> getDirection = new HashMap<>();
    getDirection.put('N', 0.0);
    getDirection.put('E', 90.0);
    getDirection.put('S', 180.0);
    getDirection.put('W', 270.0);

    // This solution will attempt to use math to minimize the number of edge cases
    // The general solution is for a string of different lengths:
    // ABC = ( A + (B+C)/2 )/2
    // AB  = ( A + B )/2
    // A   = A
    // In other words, you take the average of the last two characters' directions
    // then take the average of what's remaining.

    int numTests = in.nextInt();
    for(int test=0; test<numTests; test++) {
      String inputRaw = in.next();
      char[] input = inputRaw.toCharArray();
      int n = input.length;

      double direction = 0;
      if(n >= 2) {
        // Get the average of the last two digits
        double secondToLastDigit = getDirection.get(input[n - 2]);
        double lastDigit = getDirection.get(input[n - 1]);
        // Edge case: NW (since N is 360, not 0)
        if(input[n - 2] == 'N' && input[n - 1] == 'W') {
          secondToLastDigit = 360;
        }
        direction = (secondToLastDigit + lastDigit)/2;
        
        // If there are three digits, take the average of: 
        //   the first digit 
        //   and the average of the final two digits
        if(n == 3) {
          double firstDigit = getDirection.get(input[0]);
          // Edge case: NNW (since N is 360, not 0)
          if(inputRaw.equals("NNW")) {
            firstDigit = 360;
          } 
          direction = (direction + firstDigit)/2;
        }
      } else {
        direction = getDirection.get(input[0]);
      }

      System.out.printf("%s is %.1f degrees\n", inputRaw, direction);

    }


  }
}

/*

Test cases:

2
ENE
S

Output:
ENE is 67.5 degrees
S is 180.0 degrees


16
N
NNE
NE
ENE
E
ESE
SE
SSE
S
SSW
SW
WSW
W
WNW
NW
NNW

Output:
N is 0.0 degrees
NNE is 22.5 degrees
NE is 45.0 degrees
ENE is 67.5 degrees
E is 90.0 degrees
ESE is 112.5 degrees
SE is 135.0 degrees
SSE is 157.5 degrees
S is 180.0 degrees
SSW is 202.5 degrees
SW is 225.0 degrees
WSW is 247.5 degrees
W is 270.0 degrees
WNW is 292.5 degrees
NW is 315.0 degrees
NNW is 337.5 degrees


*/