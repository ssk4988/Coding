/*
ID: ssk49881
LANG: JAVA
TASK: cardgame
*/

import java.io.*;
import java.util.*;

public class cardgame {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("cardgame.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cardgame.out")));
        int numCards = Integer.parseInt(in.readLine());
        ArrayList<Integer> oppDeck = new ArrayList<>();
        ArrayList<Integer> oppDeckSorted = new ArrayList<>();
        for (int i = 0; i < numCards; i++) {
            oppDeck.add(Integer.parseInt(in.readLine()));
            oppDeckSorted.add(oppDeck.get(i));
        }
        Collections.sort(oppDeckSorted);
        ArrayList<Integer> myDeck = new ArrayList<>();
        int prev = 0;
        for (int i = 0; i < oppDeckSorted.size(); i++) {
            int card = oppDeckSorted.get(i);
            for (int j = prev + 1; j < card; j++) {
                myDeck.add(j);
            }
            prev = card;
        }
        for (int j = prev + 1; j < 2 * numCards + 1; j++) {
            myDeck.add(j);
        }
        ArrayList<Integer> oppFirst = new ArrayList<>();
        ArrayList<Integer> oppLast = new ArrayList<>();
        for (int i = 0; i < numCards / 2; i++) {
            oppFirst.add(oppDeck.get(i));
        }
        for (int i = numCards / 2; i < numCards; i++) {
            oppLast.add(oppDeck.get(i));
        }
        Collections.sort(oppFirst);
        Collections.sort(oppLast);
        int numwins = 0;
        int myIndex = myDeck.size() - 1;
        for (int i = oppFirst.size() - 1; i >= 0; i--) {
            if (oppFirst.get(i) < myDeck.get(myIndex)) {
                numwins++;
                myIndex--;
            }
        }
        myIndex = 0;
        for (int i = 0; i < oppLast.size(); i++) {
            if (oppLast.get(i) > myDeck.get(myIndex)) {
                numwins++;
                myIndex++;
            }
        }
        out.println(numwins);

        in.close();
        out.close();
    }
}