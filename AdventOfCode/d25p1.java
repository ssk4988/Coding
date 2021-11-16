import java.io.*;
import java.util.*;

public class d25p1 {
    public static void main(String[] args) throws Exception {
        long cardKey = 6929599;
        long doorKey = 2448427;
        long subjectNum = 7;
        int cardLoop = 0;
        int doorLoop = 0;
        

        long val = 1;
        while(val != cardKey){
            val *= subjectNum;
            val %= 20201227;
            cardLoop++;
        }
        System.out.println(cardLoop);
        val = 1;
        while(val != doorKey){
            val *= subjectNum;
            val %= 20201227;
            doorLoop++;
        }
        System.out.println(doorLoop);
        long encryptionKey = 1;
        subjectNum = cardKey;
        for(int i = 0; i < doorLoop; i++){
            encryptionKey *= subjectNum;
            encryptionKey %= 20201227;
        }
        long encryptionKey1 = 1;
        subjectNum = doorKey;
        for(int i = 0; i < cardLoop; i++){
            encryptionKey1 *= subjectNum;
            encryptionKey1 %= 20201227;
        }
        System.out.println(encryptionKey + " " + encryptionKey1);
    }

}
