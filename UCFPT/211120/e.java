/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line = in.readLine();
        int[][][] digits = {
            {
                {1, 1, 1, 1, 1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1, 1, 1, 1, 1}
            },
            {
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1}
            },
            {
                {1, 1, 1, 1, 1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {1, 1, 1, 1, 1},
                {1,0,0,0,0},
                {1,0,0,0,0},
                {1, 1, 1, 1, 1}
            },
            {
                {1, 1, 1, 1, 1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {1, 1, 1, 1, 1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {1, 1, 1, 1, 1}
            },
            {
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
            },
            {
                {1,1,1,1,1},
                {1,0,0,0,0},
                {1,0,0,0,0},
                {1,1,1,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {1,1,1,1,1}
            },
            {
                {1,1,1,1,1},
                {1,0,0,0,0},
                {1,0,0,0,0},
                {1,1,1,1,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1}
            },
            {
                {1,1,1,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,0,1}
            },
            {
                {1,1,1,1,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1}
            },
            {
                {1,1,1,1,1},
                {1,0,0,0,1},
                {1,0,0,0,1},
                {1,1,1,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {1,1,1,1,1}
            },
            {
                {0,0,0,0,0},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {1,1,1,1,1},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {0,0,0,0,0}
            }
        };
        int numDigits = (line.length() + 1) / 6;
        int numScanned = 0;
        int[][][] input = new int[numDigits][7][5];
        while(numScanned < 7){
            for(int i = 0; i < line.length(); i++){
                if(i%6 == 5) continue;
                int digitnum = i / 6;
                input[digitnum][numScanned][i%6] = line.charAt(i) == '.' ? 0 : 1;
            }
            numScanned++;
            if(numScanned != 7){
                line = in.readLine();
            }
                
        }
        
        for(int j = 0; j < input.length; j++){
            String d = "";
            for(int k = 0; k < input[j].length; k++){
                for(int l = 0; l < input[j][k].length; l++){
                    d += "" + input[j][k][l];
                }
                d += "\n";
            }
            //System.out.println(d);
        }
        int[] equation = new int[numDigits];
        for(int i = 0; i < equation.length; i++){
            int j;
            dig: for(j = 0; j < digits.length; j++){
                for(int k = 0; k < digits[j].length; k++){
                    for(int l = 0; l < digits[j][k].length; l++){
                        if(input[i][k][l] != digits[j][k][l]) continue dig;
                    }
                }
                equation[i] = j;
                break;
            }
            
        }
        //System.out.println(Arrays.toString(equation));
        int[] vals = {0, 0};
        int index1 = 0;
        for(int i = 0; i < equation.length; i++){
            if(equation[i] == 10){
                index1++;
                continue;
            }
            vals[index1] *= 10;
            vals[index1] += equation[i];
        }
        String answer = (vals[0] + vals[1]) + "";
        //System.out.println(answer);
        for(int i = 0; i < 7; i++){
            String s = "";
            for(int j = 0; j < answer.length(); j++){
                int digit = answer.charAt(j) - '0';
                for(int k = 0; k < 5; k++){
                    s += digits[digit][i][k] == 0 ? "." : "x";
                }
                if(j < answer.length() - 1){
                    s += ".";
                }
                
            }
            System.out.println(s);
        }
        in.close();
        out.close();
    }
}