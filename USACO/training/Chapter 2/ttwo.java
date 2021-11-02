/*
ID: ssk49881
LANG: JAVA
TASK: ttwo
*/

import java.io.*;
import java.util.*;

public class ttwo {
    public static int[][] env;
    public static int cowIndex;
    public static int farmerIndex;
    public static int cowDirection;
    public static int farmerDirection;
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("ttwo.in"));
        PrintWriter out = new PrintWriter(new File("ttwo.out"));

        env = new int[10][10];
        int i = 0;
        cowIndex = 0;
        farmerIndex = 0;
        cowDirection = 0; //0 north 1 east 2 south 3 west
        farmerDirection = 0;
        while(in.hasNextLine()){
            String phrase = in.nextLine();
            for(int j = 0; j < phrase.length(); j++){
                if(phrase.charAt(j) == '.'){
                    env[i][j] = 0;
                }
                if(phrase.charAt(j) == '*'){
                    env[i][j] = 1;
                }
                if(phrase.charAt(j) == 'C'){
                    env[i][j] = 2;
                    cowIndex = 10 * i + j;
                }
                if(phrase.charAt(j) == 'F'){
                    env[i][j] = 3;
                    farmerIndex = 10 * i + j;                                                                          
                }
            }
            i++;
        }

        int minutes = 0;

        while(cowIndex != farmerIndex && minutes < 160000){
            if(cowDirection == 0){
                if(cowIndex / 10 == 0 || env[cowIndex / 10 - 1][cowIndex % 10] == 1){
                    cowDirection = 1;
                    System.out.println("cow turn east");
                }
                else{
                    cowIndex = cowIndex - 10;
                }
            }
            else if(cowDirection == 1){
                if(cowIndex % 10 == 9 || env[cowIndex / 10][cowIndex % 10 + 1] == 1){
                    cowDirection = 2;
                    System.out.println("cow turn south");
                }
                else{
                    cowIndex = cowIndex + 1;
                }
            }
            else if(cowDirection == 2){
                if(cowIndex / 10 == 9 || env[cowIndex / 10 + 1][cowIndex % 10] == 1){
                    cowDirection = 3;
                    System.out.println("cow turn west");
                }
                else{
                    cowIndex = cowIndex + 10;
                }
            }
            else if(cowDirection == 3){
                if(cowIndex % 10 == 0 || env[cowIndex / 10][cowIndex % 10 - 1] == 1){
                    cowDirection = 0;
                    System.out.println("cow turn north");
                }
                else{
                    cowIndex = cowIndex - 1;
                }
            }
            if(farmerDirection == 0){
                if(farmerIndex / 10 == 0 || env[farmerIndex / 10 - 1][farmerIndex % 10] == 1){
                    farmerDirection = 1;
                    System.out.println("farmer turn east");
                }
                else{
                    farmerIndex = farmerIndex - 10;
                }
            }
            else if(farmerDirection == 1){
                if(farmerIndex % 10 == 9 || env[farmerIndex / 10][farmerIndex % 10 + 1] == 1){
                    farmerDirection = 2;
                    System.out.println("farmer turn south");
                }
                else{
                    farmerIndex = farmerIndex + 1;
                }
            }
            else if(farmerDirection == 2){
                if(farmerIndex / 10 == 9 || env[farmerIndex / 10 + 1][farmerIndex % 10] == 1){
                    farmerDirection = 3;
                    System.out.println("farmer turn west");
                }
                else{
                    farmerIndex = farmerIndex + 10;
                }
            }
            else if(farmerDirection == 3){
                if(farmerIndex % 10 == 0 || env[farmerIndex / 10][farmerIndex % 10 - 1] == 1){
                    farmerDirection = 0;
                    System.out.println("farmer turn north");
                }
                else{
                    farmerIndex = farmerIndex - 1;
                }
            }
            //System.out.println(cowIndex + " " + farmerIndex);
            minutes++;
        }
        if(minutes == 160000){
            out.println(0);
        }
        else{
            out.println(minutes);
        }


        in.close();
        out.close();
    }


}