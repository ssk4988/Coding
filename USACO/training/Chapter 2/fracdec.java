/*
ID: ssk49881
LANG: JAVA
TASK: fracdec
*/
import java.util.*;
import java.io.*;

public class fracdec {
	
	/*
	 * 1/7 = 0.14285714285714....
	 * 
	 * 7 | 1
	 */
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new File("fracdec.in"));
		// Scanner in = new Scanner("100000 9817");
		PrintWriter pw = new PrintWriter(new File("fracdec.out"));
		int num = in.nextInt();
		int den = in.nextInt();
		int div = num / den;
		if(num % den == 0) pw.println((double) num/den);
		else {
			StringBuilder str = new StringBuilder();
			boolean [] visited = new boolean[100010]; // checks whether number is already visited
			ArrayList <Integer> digits = new ArrayList <Integer> (); // records the digits to add the 
			ArrayList <Integer> nvalues = new ArrayList <Integer> (); // finds out when to start adding parentheses
			num %= den;
			while(num > 0 && ! visited[num]) {
				visited[num] = true;
				nvalues.add(num);
				num *= 10;
				digits.add(num / den);
				num %= den;
			}
			
			for(int i = 0; i < digits.size(); i++) {
				if(num > 0 && nvalues.get(i) == num) str.append("(");
				str.append(digits.get(i));
			}
			
			
			str.append(num > 0 ? ")" : "");
			
			String s = div + "." + str.toString();
			int at = 0;
			while(s.length()-at > 76)
			{
				pw.println(s.substring(at,at+76));
				at+=76;
			}
			if(at - s.length() != 0)
				pw.println(s.substring(at));
			
		}
		in.close();
		pw.close();
	}

}