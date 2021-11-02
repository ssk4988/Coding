/*
ID: ssk49881
LANG: JAVA
TASK: friday
*/

import java.io.*;
import java.util.*;

public class friday {
    public static void main(String[] args) throws Exception{
        Scanner in = new Scanner(new File("friday.in"));
        PrintWriter out = new PrintWriter(new File("friday.out"));
        int years = in.nextInt();
        int thirteenth = 0;
        int[] dayFreqs = {0, 0, 0, 0, 0, 0, 0};
        int[] monthLengths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for(int year = 1900; year < 1900 + years; year++){
            for(int month = 0; month < monthLengths.length; month++){
                dayFreqs[thirteenth % 7] += 1;
                if(isLeapYear(year) && month == 1){
                    thirteenth += 29;
                }
                else{
                    thirteenth += monthLengths[month];
                }
            }
        }
        //System.out.println(dayFreqs[0] + " " + dayFreqs[1] + " " + dayFreqs[2] + " " + dayFreqs[3] + " " + dayFreqs[4] + " " + dayFreqs[5] + " " + dayFreqs[6]);
        out.println(dayFreqs[0] + " " + dayFreqs[1] + " " + dayFreqs[2] + " " + dayFreqs[3] + " " + dayFreqs[4] + " " + dayFreqs[5] + " " + dayFreqs[6]);
        in.close();
        out.close();
    }
    public static boolean isLeapYear(int year){
        if (year % 400 == 0){
            return true;
        }
        else if (year % 100 == 0){
            return false;
        }
        else if (year % 4 == 0){
            return true;
        }
        else{
            return false;
        }
    }
}