// Arup Guha
// 8/9/2022
// Solution to 2022 UCF Locals Problem: Word Tree

import java.util.*;

public class wordtree {
	
	public static int n;
	public static int k;
	public static char[][] words;
	
	public static void main(String[] args) {
		
		// Read the input.
		Scanner stdin = new Scanner(System.in);
		n = stdin.nextInt();
		k = stdin.nextInt();
		words = new char[n][];
		for (int i=0; i<n; i++)
			words[i] = stdin.next().toCharArray();
			
		// Create all possible edges.
		ArrayList<edge> eList = new ArrayList<edge>();
		for (int i=0; i<n; i++)
			for (int j=i+1; j<n; j++)
				eList.add(new edge(i, j, cost(i,j)));
				
		// Sort for Kruskal's.
		Collections.sort(eList);
		int numE = 0;
		
		// Set up our disjoint set.
		djset dj = new djset(n);
		int idx = 0, res = -1;
		
		while (numE < n-1) {
		
			// Get next edge, skip if can't use.
			edge e = eList.get(idx++);
			boolean fuse = dj.union(e.u, e.v);
			if (!fuse) continue;
			
			// New edge add it.
			numE++;
			
			// If we always assign, max edge weight will be correct at end.
			res = e.w;
		}
		
		// Ta da!
		System.out.println(res);
	}
	
	// Returns the edge cost between words i and j.
	public static int cost(int i, int j) {
		int res = 0;
		for (int z=0; z<k; z++)
			res += Math.abs(words[i][z]-words[j][z]);
		return res;
	}

}

class edge implements Comparable<edge> {
	
	public int u;
	public int v;
	public int w;
	
	public edge(int myu, int myv, int myw) {
		u = myu;
		v = myv;
		w = myw;
	}
	
	public int compareTo(edge other) {
		return this.w - other.w;
	}
}

// Disjoint set class with path compression.
class djset {

	public int n;
	public int[] par;
	
	public djset(int myn) {
		n = myn;
		par = new int[n];
		for (int i=0; i<n; i++)
			par[i] = i;
	}
	
	public int find(int v) {
		if (par[v] == v) return v;
		return par[v] = find(par[v]);
	}
	
	public boolean union(int u, int v) {
		u = find(u);
		v = find(v);
		if (u == v) return false;
		par[v] = u;
		return true;
	}
}