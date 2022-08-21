package solutions.most;

import java.util.*;

class most {

	static Scanner bob;

	static ArrayList<ArrayList<Pair>> adjList;
	static RMQ rmq;

	static ArrayList<Pair> lcaPairs;
	static int[] lcaLocs, parents;

	static int LOG;
	static int[][] up, mxUpEven, mxUpOdd;
	public static void main(String[] args) {
		bob = new Scanner(System.in);
		int t = bob.nextInt();
		for (int tt = 0; tt < t; tt++)
			System.out.println(solve(tt));
	}

	static long solve(int t) {
		int n = bob.nextInt(), m = bob.nextInt();

		Edge[] edges = new Edge[m];
		for (int e = 0; e < m; e++)
			edges[e] = new Edge(
				bob.nextInt() - 1,
				bob.nextInt() - 1,
				bob.nextInt()
			);

		HashMap<Pair, Integer> connections = new HashMap<Pair, Integer>();
		adjList = new ArrayList<ArrayList<Pair>>();
		for (int i = 0; i < n; i++) adjList.add(new ArrayList<Pair>());

		boolean[] inMST = new boolean[m];
		DisjointSet dsu = new DisjointSet(n);
		Arrays.sort(edges);
		long mst = 0;
		for (int i = 0; i < m; i++) {
			Edge e = edges[i];
			if (dsu.union(e.u, e.v)) {
				inMST[i] = true;

				connections.put(new Pair(e.u, e.v), e.w);
				connections.put(new Pair(e.v, e.u), e.w);

				adjList.get(e.u).add(new Pair(e.v, e.w));
				adjList.get(e.v).add(new Pair(e.u, e.w));
				mst += e.w;
			}
		}
		// It's already odd, yay! n_n
		if (mst % 2 == 1)
			return mst;

		// Sigh... We need to make it odd, let's do the following:
		//	for each edge (u, v) NOT in the MST
		//		find maximum edge on path from (u, v) of opposite parity to add
		//		consider replacing it, update new MOST

		// How can we find the maximum edge on a path from u -> v?
		// Find LCA
		// Binary lift on max

		// Build RMQ to find LCA of an (u, v) pair
		lcaPairs = new ArrayList<Pair>();
		lcaLocs = new int[n];
		parents = new int[n];
		getLcaPairs(adjList, 0, 0, 0);

		Pair[] lcaPairsAsArray = new Pair[lcaPairs.size()];
		for (int i = 0; i < lcaPairs.size(); i++) lcaPairsAsArray[i] = lcaPairs.get(i);
		rmq = new RMQ(lcaPairsAsArray);

		// Build binary lifting parents and maxs
		LOG = 0;
		int sz = n;
		while (sz > 0) {
			LOG++;
			sz /= 2;
		}

		// Construct lift table
		up = new int[n][LOG];
		mxUpEven = new int[n][LOG];
		mxUpOdd = new int[n][LOG];
		fill2D(mxUpEven, -1);
		fill2D(mxUpOdd, -1);

		for (int u = 0; u < n; u++) {
			int v = parents[u];
			up[u][0] = v;
			int w = connections.getOrDefault(new Pair(u, v), -1);
			if (w % 2 == 0) mxUpEven[u][0] = w;
			else mxUpOdd[u][0] = w;
		}

		for (int lg = 1; lg < LOG; lg++) {
			for (int u = 0; u < n; u++) {
				up[u][lg] = up[ up[u][lg-1] ][lg-1];
				mxUpEven[u][lg] = Math.max(mxUpEven[u][lg-1], mxUpEven[ up[u][lg-1] ][lg-1]);
				mxUpOdd[u][lg] = Math.max(mxUpOdd[u][lg-1], mxUpOdd[ up[u][lg-1] ][lg-1]);
			}
		}

		// For every edge, try to add it in
		long MOST = Long.MAX_VALUE;
		for (int i = 0; i < m; i++) {
			if (inMST[i]) continue;

			Edge e = edges[i];

			// If our edge is odd, then we want to remove the max even
			int removal = -1;

			if (e.w % 2 == 0) removal = maxEdgeOnPath(e.u, e.v, mxUpOdd);
			else removal = maxEdgeOnPath(e.u, e.v, mxUpEven);

			if (removal == -1) continue;

			MOST = Math.min(MOST, mst - removal + e.w);
		}

		if (MOST == Long.MAX_VALUE) return -1;
		return MOST;
	}

	static int lca(int u, int v) {
		int lo = lcaLocs[u];
		int hi = lcaLocs[v];
		return rmq.query(Math.min(lo, hi), Math.max(lo, hi)).b;
	}

	static int maxEdgeOnPath(int u, int v, int[][] mxLiftParity) {
		int l = lca(u, v);
		int depthL = lcaPairs.get(lcaLocs[l]).a;
		int depthU = lcaPairs.get(lcaLocs[u]).a - depthL;
		int depthV = lcaPairs.get(lcaLocs[v]).a - depthL;

		int mx = -1;
		for (int k = LOG - 1; k >= 0; k--) {
			int mask = 1 << k;
			if ((depthU & mask) != 0) {
				mx = Math.max(mx, mxLiftParity[u][k]);
				u = up[u][k];
			}
			if ((depthV & mask) != 0) {
				mx = Math.max(mx, mxLiftParity[v][k]);
				v = up[v][k];
			}
		}
		return mx;
	}

	static void fill2D(int[][] arr, int val) {
		for (int[] v : arr) {
			Arrays.fill(v, val);
		}
	}

	static void getLcaPairs(ArrayList<ArrayList<Pair>> adjList, int cur, int parent, int depth) {
		Pair id = new Pair(depth, cur);
		parents[cur] = parent;
		lcaLocs[cur] = lcaPairs.size();
		lcaPairs.add(id);
		for (Pair p : adjList.get(cur))
			if (p.a != parent) {
				getLcaPairs(adjList, p.a, cur, depth + 1);
				lcaPairs.add(id);
			}
	}

	static class Pair implements Comparable<Pair> {
		int a, b;
		public Pair(int _a, int _b) {
			a = _a;
			b = _b;
		}
		public int compareTo(Pair o) {
			if (a < o.a) return -1;
			if (a == o.a) return 0;
			return 1;
		}
		static Pair minPair(Pair a, Pair b) {
			if (a.compareTo(b) == -1) return a;
			return b;
		}

		// gen
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + a;
			result = prime * result + b;
			return result;
		}
		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Pair other = (Pair) obj;
			if (a != other.a)
				return false;
			if (b != other.b)
				return false;
			return true;
		}
	}

	static class Edge implements Comparable<Edge> {
		int u, v;
		int w;
		public Edge(int _u, int _v, int _w) {
			u = _u;
			v = _v;
			w = _w;
		}
		public int compareTo(Edge o) {
			if (w < o.w) return -1;
			if (w == o.w) return 0;
			return 1;
		}
	}


	static class DisjointSet {
		int[] s;
		public DisjointSet(int n) {
			Arrays.fill(s = new int[n], -1);
		}
		public int find(int i) {
			return s[i] < 0 ? i : (s[i] = find(s[i]));
		}
		public boolean union(int a, int b) {
			if ((a = find(a)) == (b = find(b))) return false;
			if(s[a] == s[b]) s[a]--;
			if(s[a] <= s[b]) s[b] = a; else s[a] = b;
			return true;
		}
	}

	static class RMQ {
		Pair[] vs;
		Pair[][] lift;
		public RMQ(Pair[] vs) {
			this.vs = vs;
			int n = vs.length;
			int maxlog = Integer.numberOfTrailingZeros(Integer.highestOneBit(n)) + 2;
			lift = new Pair[maxlog][n];
			for (int i = 0; i < n; i++)
				lift[0][i] = vs[i];
			int lastRange = 1;
			for (int lg = 1; lg < maxlog; lg++) {
				for (int i = 0; i < n; i++) {
					lift[lg][i] = Pair.minPair(lift[lg - 1][i], lift[lg - 1][Math.min(i + lastRange, n - 1)]);
				}
				lastRange *= 2;
			}
		}
		public Pair query(int low, int hi) {
			int range = hi - low + 1;
			int exp = Integer.highestOneBit(range);
			int lg = Integer.numberOfTrailingZeros(exp);
			return Pair.minPair(lift[lg][low], lift[lg][hi - exp + 1]);
		}
	}
}
