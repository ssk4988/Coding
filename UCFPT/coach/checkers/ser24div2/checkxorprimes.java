// Arup Guha
// 8/7/2025
// Checker for UCF Locals Problem: Xor Primes

import java.util.*;
import java.io.*;

public class checkxorprimes {

	public static void main(String[] args) throws Exception {

		// args[0] = real input
		// args[1] = student output
		// args[2] = real output

		Scanner inp = new Scanner(new File(args[0]));
		BufferedReader studout = new BufferedReader(new FileReader(args[1]));

        // Get from input.
		int n = inp.nextInt();

        // Make sure input is there.
		String line = "";
		if (studout.ready()) line = studout.readLine();
		else {
			System.out.println("No output.");
			return;
		}

        // Tokenize. If too many tokens then immediately this is bad.
		StringTokenizer tok = new StringTokenizer(line);
		if (tok.countTokens() > 100) {
			System.out.println("Too many tokens.");
			return;
		}
		
		// Try adding all tokens in student output as ints in a list.
		ArrayList<Integer> primes = new ArrayList<Integer>();
		while (tok.hasMoreTokens()) {
			try {
				int x = Integer.parseInt(tok.nextToken());
				primes.add(x);
			}
			catch (Exception e) {
				System.out.println("not an integer.");
			}
		}
		
		// Here we check if each number is in range and is prime.
		int xor = 0;
		for (int i=0; i<primes.size(); i++) {
			int cur = primes.get(i);
			if (!isprime(cur)) System.out.println("not prime");
			if (cur >= 2100000000) System.out.println("too big");
			xor = xor ^ cur;
		}
		
		// Lastly, we check the XOR
		if (xor != n)
			System.out.println("xor doesn't work");

        // Can't have more stuff.
		if (studout.ready()) System.out.println("too much output");
		
	}
	
	public static boolean isprime(int n) {
		if (n<2) return false;
		for (int i=2; i*i<=n; i++)
			if (n%i == 0)
				return false;
		return true;
	}
}
