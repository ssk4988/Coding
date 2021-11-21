// Checker for 2018 GCPC Problem L: Hyper Illuminati
// Arup Guha
// 11/12/2020

import java.io.File;
import java.io.IOException;
import java.util.*;

public class check_j {
	
	final public static int[] DX = {-1,-1,-1,0,0,0,1,1,1};
	final public static int[] DY = {-1,0,1,-1,0,1,-1,0,1};

	static File judgeIn, judgeOut, teamOut;
	static Scanner judge, team, in;

	public static void main(String[] args) {
		// CHECK ARGUMENTS
		if (args.length < 3)
			die("Please provide 3 filenames as arguments: <judgeIn> <teamOut> <judgeOut>");

		// CREATE FILES/SCANNERS
		try {
			judgeIn  = new File(args[0]);
			judgeOut = new File(args[1]);
			teamOut  = new File(args[2]);

			in = new Scanner(judgeIn);
			judge = new Scanner(judgeOut);
			team  = new Scanner(teamOut);
		} catch (IOException ioe) {
			ioe.printStackTrace(System.out);
			die("Failed to open judgement files!");
		}

		// Get input.
		int r = in.nextInt();
		int c = in.nextInt();
		int[][] g = new int[r+2][c+2];
		for (int i=0; i<g.length; i++)
			for (int j=0; j<g[0].length; j++)
				g[i][j] = in.nextInt();
		in.close();
		
		// Get correct answer.
		ArrayList<String> jAns = new ArrayList<String>();
		while (judge.hasNext()) jAns.add(judge.next());
		judge.close();
		

		// READ TEAM ANSWER
		ArrayList<String> teamAns = new ArrayList<String>();
		while (team.hasNext()) teamAns.add(team.next());
		
		// Impossible case.
		if (jAns.size() == 1 && jAns.get(0).equals("impossible")) {
			if (teamAns.size() != 1) die("wrong # of lines");
			if (!teamAns.get(0).equals("impossible")) die("wrong ans it is impossible");
		}
		
		// Reg case.
		else {
			
			// Not the right # or rows.
			if (teamAns.size() != r) die("Wrong # of rows");
			
			// Not valid format of a row.
			for (int i=0; i<r; i++)
				if (badRow(teamAns.get(i), c))
					die("bad row form");
				
			// Make the team grid.
			int[][] teamGrid = getTeamGrid(teamAns);
			
			// See if the grids are equal.
			if (!equal(g, teamGrid)) die("wrong answer");
		}
		
		// ##############################
		// ## The Solution is Accepted ##
		// ##############################
		
		// CLOSE SCANNERS
		team.close();
	}
	
	// Returns true if a and b are identical.
	static boolean equal(int[][] a, int[][] b) {
		
		// # rows don't match.
		if (a.length != b.length) return false;
		
		// Check each row.
		for (int i=0; i<a.length; i++) {
			
			// Cols don't match.
			if (a[i].length != b[i].length) return false;
			
			// Look for mismatched elements.
			for (int j=0; j<a[i].length; j++) {
				if (a[i][j] != b[i][j]) return false;
			}
		}
		
		// Good if we get here.
		return true;
		
	}
	
	// Return the corresponding int array.
	static int[][] getTeamGrid(ArrayList<String> lines) {
		
		// Store it.
		int[][] res = new int[lines.size()+2][lines.get(0).length()+2];
		
		// Go to each cell.
		for (int i=0; i<lines.size(); i++) 
			for (int j=0; j<lines.get(0).length(); j++)

				// Here are where the contributions are made.
				if (lines.get(i).charAt(j) == 'X') 
					for (int z=0; z<DX.length; z++) 
						res[i+1+DX[z]][j+1+DY[z]]++;
				
		// Ta da!
		return res;
	}
	
	// Returns true if s is a bad row.
	static boolean badRow(String s, int size) {
		
		// Not the right length.
		if (s.length() != size) return true;
		
		// Only valid characters.
		for (int i=0; i<size; i++)
			if (s.charAt(i) != '.' && s.charAt(i) != 'X')
				return true;
			
		// not bad if we make it here.
		return false;
	}

	/* =============== UTILITIES =============== */
	
	// Check for a line and return it if it's there.
	static String readLine(Scanner sc) {
		if (!sc.hasNextLine())
			die("No line when there should be one");
		return sc.nextLine();
	}
	
	// Call when we expect a line to contain n integers in between low and high, inclusive.
	static int[] convertToIntsInRange(String s, int n, int low, int high) {
		StringTokenizer tok = new StringTokenizer(s);
		if (tok.countTokens() != n)
			die("Wrong tok cnt wanted "+n+" got "+tok.countTokens()+" "+s);
		int[] res = new int[n];
		for (int i=0; i<n; i++) {
			
			try {
				res[i] = Integer.parseInt(tok.nextToken());
			} 
			catch (NumberFormatException ne) {
				ne.printStackTrace(System.out);
				die("Not a number");
			}
			
			if (res[i] < low || res[i] > high)
				die("Number out of range");
		}
		
		return res;
	}
	
	// Returns true iff arr has unique values only.
	static boolean unique(int[] arr) {
		HashSet<Integer> set = new HashSet<Integer>();
		for (int i=0; i<arr.length; i++) {
			if (set.contains(arr[i])) return false;
			set.add(arr[i]);
		}
		return true;
	}

	// CHECK FOR PRESENCE OF INTEGER, AND REPORT
	static int readInt(Scanner sc) {
		if (!sc.hasNextInt())
			die("Could not read integer!");
		return sc.nextInt();
	}

	// CHECK FOR PRESENCE OF TOKEN, AND REPORT
	static String readToken(Scanner sc) {
		if (!sc.hasNext())
			die("Could not read token!");
		return sc.next();
	}

	// PRINT msg AND TERMINATE
	static void die(String msg) {
		System.out.println(msg);
		System.exit(0);
	}

}
