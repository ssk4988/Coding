import java.io.*;
import java.util.*;

public class i {
    static int[] daysm = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static int dywk = 5; //1999 last day friday
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int year = Integer.parseInt(in.readLine());

        int prevyearday = dywk;
        for(int y = 2000; y < year; y++){
            prevyearday = (prevyearday + (isLeap(y) ? 366 : 365)) % 7;
        }
        if(isLeap(year)){
            daysm[1] = 29;
        }
        int mom = prevyearday;
        int dad = prevyearday;
        for(int i = 0; i < 4; i++){
            mom = (mom + daysm[i]) % 7;
        }
        for(int i = 0; i < 5; i++){
            dad = (dad + daysm[i]) % 7;
        }
        int mcnt = 0;
        int dcnt = 0;
        int mday = 0, dday = 0;
        while(mcnt < 2){
            mom = (mom + 1) % 7;
            mday++;
            if(mom == 0) mcnt++;
        }
        while(dcnt < 3){
            dad = (dad + 1) % 7;
            dday++;
            if(dad == 0) dcnt++;
        }
        int diff = dday - mday + 31;
        if(diff == 35){
            System.out.println("5 weeks");
        }
        else if(diff == 42){
            System.out.println("6 weeks");
        }
        in.close();
    }
    static boolean isLeap(int year){
        if(year % 400 == 0) return true;
        if(year % 100 == 0) return false;
        if(year % 4 == 0) return true;
        return false;
    }
}