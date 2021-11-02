/*
ID: ssk49881
LANG: JAVA
TASK: highcard
*/

import java.io.*;
import java.util.*;

public class highcard {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("highcard.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("highcard.out")));
        int numCards = Integer.parseInt(in.readLine());
        ArrayList<Integer> oppDeck = new ArrayList<>();
        for (int i = 0; i < numCards; i++) {
            oppDeck.add(Integer.parseInt(in.readLine()));
        }
        Collections.sort(oppDeck);
        ArrayList<Integer> myDeck = new ArrayList<>();
        int prev = 0;
        for (int i = 0; i < oppDeck.size(); i++) {
            int card = oppDeck.get(i);
            for (int j = prev + 1; j < card; j++) {
                myDeck.add(j);
            }
            prev = card;
        }
        for (int j = prev + 1; j < 2 * numCards + 1; j++) {
            myDeck.add(j);
        }
        int numwins = 0;
        int myIndex = myDeck.size() - 1;
        for (int i = oppDeck.size() - 1; i >= 0; i--) {
            if (oppDeck.get(i) < myDeck.get(myIndex)) {
                numwins++;
                myIndex--;
            }
        }
        out.println(numwins);

        in.close();
        out.close();
    }
}