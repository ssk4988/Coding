// Arup Guha
// 8/12/2022
// Alternate Solution to 2022 UCF Locals Problem: Maximum Satisfaction

import java.util.*;

public class maxsat_alt {

	public static int nStud;
	public static int nSec;
	public static int minEnroll;
	
	public static int[][] ratings;
	public static int[] max;
	public static int sumMax;
	
	public static void main(String[] args) {
	
		// Get basic input.
		Scanner stdin = new Scanner(System.in);
		nStud = stdin.nextInt();
		nSec = stdin.nextInt();
		minEnroll = stdin.nextInt();
	
		// Read ratings data. Store max rating for each student and their sum.
		ratings = new int[nStud][nSec];
		max = new int[nStud];
		sumMax = 0;
		for (int i=0; i<nStud; i++) {
			for (int j=0; j<nSec; j++) {
				ratings[i][j] = stdin.nextInt();
				max[i] = Math.max(max[i], ratings[i][j]);
			}
			sumMax += max[i];
		}
		
		int[][] tableau = new int[nStud][nStud];
		
		// Now fill in costs of matching each student to each "position"
		for (int i=0; i<nStud; i++) {
		
			// For each section.
			for (int j=0; j<nSec; j++) 
				for (int k=0; k<minEnroll; k++)
					tableau[i][j*minEnroll+k] = max[i] - ratings[i][j];
					
			// Note that the rest of the tableau from column nSec*minEnroll to nStud-1 are 
			// already set to 0 representing matching students to their best section.
		}
		
		// Run the Hungarian Algorithm.
		int sub = Hungarian.hungarian(tableau);
		
		// Answer is maximum sum of satisfaction, minus the minimum cost of doing the matching between positions.
		System.out.println(sumMax - sub);
	}
}

class Hungarian {

	// finds MINIMUM cost of matching every row to some col,
	// using each col at most once in O(n^2 * m)
	// ** nRows must be <= nCols **
	// rowMatchWith[i] = the column that row i matched with
	public static int[] rowMatchesWith;

	public static int hungarian(int[][] a) {

		int n=a.length, m=a[0].length; if (n>m) throw null;
		int[] u=new int[n], v=new int[m+1]; //edge (i->j) >= u[i]+v[j]
		int[] p=new int[m+1]; //p[j] = left match for right node j
		Arrays.fill(p, -1);

		for (int i=0; i<n; i++) {//find alternating path for node i
			int j0=m; p[j0]=i;
			int[] dist=new int[m+1], from=new int[m+1];
			boolean[] seen=new boolean[m+1];
			Arrays.fill(dist, Integer.MAX_VALUE);
			Arrays.fill(from, -1);

			while (p[j0]!=-1) {

				seen[j0]=true; int i0=p[j0], delta=Integer.MAX_VALUE, j1=-1;
				for (int j=0; j<m; j++) {//consider edges i0 -> everything
					if (seen[j]) continue;
					int candDist=a[i0][j]-u[i0]-v[j];
					if (candDist<dist[j]) {dist[j]=candDist; from[j]=j0;}
					if (dist[j]<delta) {delta=dist[j]; j1=j;}
				}
				
				//it costs at least delta to get somewhere else,
				//subtract that from all distances and add cost to u, v, arrays
				//from all done -> not done edges
				for (int j=0; j<=m; j++) {
					if (seen[j]) {u[p[j]]+=delta; v[j]-=delta;}
					else dist[j]-=delta;
				}

				j0=j1;
			}
			
			//flip alternating path
			while (j0!=m) { int j1=from[j0]; p[j0]=p[j1]; j0=j1; }
		}
		
		//sum of deltas is stored at v[m] coincidentally
		int ans=-v[m];
		rowMatchesWith=new int[n];
		for (int j=0; j<m; j++) 
			if (p[j]!=-1) rowMatchesWith[p[j]]=j;

		return ans;
	}
	
}