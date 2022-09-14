//
// 2022 UCF Local Programming Contest (Final Round) -- freq
// Ali Orooji
//

import java.util.*;
import java.lang.Math;

public class freq
{
	public static final int MAX_NUM_OF_CHARS = 30;
	
	public static final int NUM_OF_ALPHABETS = 26;
	
	public static final String ALPHABETS = "abcdefghijklmnopqrstuvwxyz";
	
	public static String word_str[];    // the input words in string
	public static char   word_char[][]; // the input words in char
	public static int    word_len[];    // length of each input word
	
	public static int num_of_words;
	
	public static int letter_freq[];
	
	public static Scanner input;
	
   /* ********************************************************* */
	
   public static void main(String[] args)
   {
	  input = new Scanner(System.in);
	  
	  num_of_words = input.nextInt();
	  
	  word_str  = new String[num_of_words];
	  word_char = new char[num_of_words][MAX_NUM_OF_CHARS + 1];
	  word_len  = new int[num_of_words];
	  
	  for (int k = 0;  k < num_of_words;  ++k)
	  {
		  word_str[k] = input.next();
		  
		  word_len[k]  = word_str[k].length();
		  word_char[k] = word_str[k].toCharArray();
		  
	  }// end for (k)
		  
	  solve();
	   
   }// end of main()

   /* ********************************************************* */
	
   public static void solve()
   {
	  letter_freq = new int[NUM_OF_ALPHABETS];
	  
	  // find the maximum word length 
	  int max_word_len = find_max_word_length();
	  
	  // go thru each position and print the results for that position
	  for (int pos = 0;  pos < max_word_len;  ++pos)
	  {
		  find_freq_at_position(pos);
		  int max_freq = find_max_freq();
		  
		  System.out.print( (pos + 1) + ":" );
		  for (int k = 0;  k < NUM_OF_ALPHABETS;  ++k)
		  {
			  if (letter_freq[k] == max_freq)
				  System.out.print( " " + ALPHABETS.charAt(k) );
		  }
		  System.out.println();
		  
	  }// end for (pos)
	   
   }// end of solve()

   /* ********************************************************* */
	
   public static int find_max_word_length()
   {
	  // find the maximum word length

	  int max = 0;
	  for (int k = 0;  k < num_of_words;  ++k)
		  if (word_len[k] > max)
			  max = word_len[k];

	  return(max);
	   
   }// end of find_max_word_length()
 
   /* ********************************************************* */
	
   public static void find_freq_at_position(int pos)
   {
	  // find the frequency for each letter at position 'pos'
	  
	  Arrays.fill(letter_freq, 0);
	  for (int k = 0;  k < num_of_words;  ++k)
	  {
		  if (word_len[k] > pos)
			  letter_freq[word_char[k][pos] - 'a'] += 1;
	  }

   }// end of find_freq_at_position()

   /* ********************************************************* */
	
   public static int find_max_freq()
   {
	  // find the maximum frequency
	  
	  int max = 0;
	  for (int k = 0;  k < NUM_OF_ALPHABETS;  ++k)
		  if (letter_freq[k] > max)
			  max = letter_freq[k];

	  return(max);
	   
   }// end of find_max_freq()

   /* ********************************************************* */
 
}// end of class freq

   /* ********************************************************* */
