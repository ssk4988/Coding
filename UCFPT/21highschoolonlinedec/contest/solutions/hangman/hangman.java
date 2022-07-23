package solutions.hangman;

import java.util.*;

public class hangman{
    public static boolean isValid(String q, String w){
        
        //If the query and the word are not the same length, it cannot be this word
        if(q.length()!=w.length()) return false;
        
        //Initialize boolean arrays to check if a letter has been called or not
        boolean letterUsed[] = new boolean[26];
        boolean isOpen[] = new boolean[26];

        //loop through word.
        for(int i = 0; i < q.length(); i++){

            //if we have a letter, check if it is the same and mark it as used, else mark it as open
            if(q.charAt(i) != '_'){
                if(q.charAt(i)!=w.charAt(i)) return false;
                letterUsed[q.charAt(i)-'a'] = true;
            }
            else{
                isOpen[w.charAt(i)-'a'] = true;
            }
        }

        //Check if there is a contradiction (a letter that is both used and open)
        for(int i = 0; i < 26; i++)
            if(letterUsed[i] && isOpen[i])
                return false;

        //If nothing else has been returned, then the word must be valid
        return true;
    }

    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);

        int c = in.nextInt();
        for(int cc = 0; cc < c; cc++){

            //get category
            String category = in.next();

            //get dictionary
            int n = in.nextInt();
            String dictionary[] = new String[n];
            for(int i = 0; i < n; i++)
                dictionary[i] = in.next();

            //get and process queries
            int g = in.nextInt();
            for(int i = 0; i < g; i++){

                //scan query
                String query = in.next();
                boolean good = false;

                //check if query works for at least one word in a dictionary
                for(String word : dictionary){
                    if(isValid(query, word)){
                        good = true;
                        break;
                    }
                }

                //Output the answer
                if(good)
                    System.out.println("No cheaters here!");
                else
                    System.out.println("That's not a word for a(n) " + category + "!");
            }
        }
        in.close();
    }
}
