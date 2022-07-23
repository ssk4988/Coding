package solutions.rocks;

import java.util.*;
public class rocks {
	static final long max = Long.MAX_VALUE / 8;

	static int n, m, M, a, b, finalTime;
	static int[] timeToTake;
	static ArrayDeque<edge>[] edges;

	static long[][][] d;
	public static void main(String[] args) {
		// the solution here is going to involve a bitmask DP

		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for(int tt = 1; tt <= t; ++tt) {
			finalTime = sc.nextInt();
			a = sc.nextInt();
			b = sc.nextInt();
			// add 2 to n to account for start and finish nodes
			n = sc.nextInt() + 2;
			m = sc.nextInt();

			// timeToTake will store the time it would take to attend the rock wall/concert at a
			// given node; if it is -1, then that means there is not a rock wall/concert at this node
			timeToTake = new int[n];
			Arrays.fill(timeToTake, -1);
			for(int i = 1; i < n - 1; ++i) {
				int numWalls = sc.nextInt(), numConcerts = sc.nextInt();
				if(numWalls == 1) timeToTake[i] = a;
				if(numConcerts == 1) timeToTake[i] = b;
			}

			// scan edges
			edges = new ArrayDeque[n];
			for(int i = 0; i < n; ++i) edges[i] = new ArrayDeque<>();
			for(int i = 0; i < m; ++i) {
				int a = sc.nextInt(), b = sc.nextInt(), w = sc.nextInt();
				edges[a].add(new edge(b, w));
				edges[b].add(new edge(a, w));
			}

			// M will simply store 2^n, which is the number of bitmasks that we will need for our table
			M = 1 << n;
			// this array d stores the minimum time to get to a node, with a given number of rock
			// walls/concerts taken, and a given mask containing information on which nodes we've
			// already seen; if we have a 1 in the mask, that means we have already visited that node
			d = new long[n][n - 1][M];
			for(long[][] z : d) {
				for(long[] y : z) {
					// we will fill the array with a big value so that we can continually improve
					// distances as we go
					Arrays.fill(y, max);
				}
			}

			// set our starting state to a distance of zero
			d[0][0][1] = 0;
			// iterate over smaller masks first and compute the future dp values for future masks;
			// this way of doing it always ensures that when we see a mask, we have already seen
			// all subsets of this mask which is key
			for(int mask = 1; mask < M; ++mask) {
				for(int idx = 0; idx < n; ++idx) {
					for(int num = 0; num < n - 1; ++num) {
						// try taking each edge and updating the table off of them
						for(edge e : edges[idx]) {
							int newIdx = e.v, newMask = mask | (1 << newIdx);

							// if newMask == mask, then the node we are trying to visit we have already
							// visited in this current state
							if(newMask == mask) continue;

							// try not taking anything here (going to the next node but not visiting the
							// rock wall/concert);
							// add the edge weight to our newD (the time to get to the next state); 
							// num stays the same
							long newD = d[idx][num][mask] + e.w;
							// only update if we have reached our new state with a smaller time
							if(newD < d[newIdx][num][newMask]) {
								// update table
								d[newIdx][num][newMask] = newD;
							}

							// try taking the rock here (going to the next node and visiting the
							// rock wall/concert)
							if(timeToTake[newIdx] != -1) {
								// if timeToTake[newIdx] was -1, then that means there is no rock wall/concert
								// at newIdx and therefore we don't have the option to take a rock wall/concert;

								// add one to num since we are choosing to take the rock wall/concert here
								int newNum = num + 1;
								// add the time it would take to attend the rock wall/concert to our newD (the time)
								newD += timeToTake[newIdx];
								if(newNum < n - 1 && newD < d[newIdx][newNum][newMask]) {
									d[newIdx][newNum][newMask] = newD;
								}
							}
						}
					}
				}
			}

			// see if we can find a positive answer; start by looking at our biggest possible
			// answer and see if we can achieve it; if not, keep looking at lower answers
			boolean foundAns = false;
			for(int out = n - 2; out >= 0 && !foundAns; --out) {
				for(int mask = 1; mask < M && !foundAns; ++mask) {
					// check if we can get this number of rocks within our time constraint
					if(d[n - 1][out][mask] <= finalTime) {
						System.out.println(out);
						// if we have found an answer, we can stop looking
						foundAns = true;
					}
				}
			}

			// we have found no suitable answer to visit all nodes, 
			// even if we skipped all rock walls/concerts
			if(!foundAns) {
				System.out.println("Book a flight!");
			}
		}
	}
	static class edge{
		int v, w;
		edge(int vv, int ww){
			v = vv;
			w = ww;
		}
	}
}
/*
sample data for convenience:

3
15 8 1
3 6
1 0
0 1
1 0
0 1 5
0 2 2
1 3 4
2 3 1
3 4 1
0 4 6
9 1 100
4 8
0 0
0 1
0 1
0 1
0 3 4
0 2 3
3 5 2
0 1 5
2 3 2
2 4 1
4 5 3
1 3 1
100 1 1
1 2
1 0
0 1 100
1 2 100

 */
