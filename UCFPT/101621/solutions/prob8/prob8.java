// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #8: Snake Game

import java.util.*;

public class prob8 {

	final public static int[] DX = {-1,0,0,1};
	final public static int[] DY = {0,-1,1,0};
	final public static int[] OFFSET = {-10, -1, 1, 10};

	public static int r;
	public static int c;
	public static int n;
	public static char[][] grid;

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Go through each case.
		for (int loop=1; loop<=numCases; loop++) {

			r = stdin.nextInt();
			c = stdin.nextInt();
			n = stdin.nextInt();

			// Read in the grid.
			grid = new char[r][];
			for (int i=0; i<r; i++)
				grid[i] = stdin.next().toCharArray();

			// Output result.
			System.out.println("Game #"+loop+": "+bfs());
		}
	}

	public static int bfs() {

		// Set up BFS.
		HashMap<Integer,Integer> map = new HashMap<Integer,Integer>();
		LinkedList<Integer> q = new LinkedList<Integer>();

		// Put initial state in bfs.
		int target = getTarget();
		int snake = getSnake();
		q.offer(snake);
		map.put(snake, 0);

		// Run until the queue is empty.
		while (q.size() > 0) {

			// Get next snake.
			int cur = q.poll();

			// We made it!
			if (intersect(cur, target)) return map.get(cur);

			// Get places snake could go next.
			ArrayList<Integer> next = getNext(cur);

			// Try enqueing all of these.
			for (int item: next) {

				// Been here before.
				if (map.containsKey(item)) continue;

				// Store this distance and put in queue.
				map.put(item, map.get(cur)+1);
				q.offer(item);
			}
		}

		// Never found the target :(
		return -1;
	}

	// The head will always be the first item to intersect the target, so just check that!
	public static boolean intersect(int curMask, int target) {
		return (curMask >> (2*n-2)) == target;
	}

	// Just look for the x and return its 1 integer equivalent.
	public static int getTarget() {
		for (int i=0; i<r; i++)
			for (int j=0; j<c; j++)
				if (grid[i][j] == 'x')
					return 10*i+j;
		return -1;
	}

	// Gets the mask of the initial snake.
	public static int getSnake() {

		int[] pos = new int[n];

		// Store all the positions of the snake.
		for (int i=0; i<r; i++)
			for (int j=0; j<c; j++)
				if (grid[i][j] >= '0' && grid[i][j] <= '9')
					pos[grid[i][j] - '0'] = 10*i + j;

		// Starting mask is where head is.
		int mask = pos[0];

		// Build the rest of the mask: 0 = up, 1 = left, 2 = right, 3 = down. (stored in OFFSET)
		for (int i=1; i<n; i++) {
			int diff = pos[i] - pos[i-1];
			for (int j=0; j<4; j++)
				if (diff == OFFSET[j])  mask = (mask << 2) + j;
		}

		// Here is our mask.
		return mask;
	}

	public static ArrayList<Integer> getNext(int snake) {

		// Store next list here.
		ArrayList<Integer> next = new ArrayList<Integer>();

		// Extract front of the snake and the direction of it.
		int pos = snake >> (2*n-2);
		int dir = snake & ((1 << (2*n-2)) - 1);
		int xPos = pos/10;
		int yPos = pos%10;

		// Go through each move.
		for (int i=0; i<DX.length; i++) {
			int x = xPos - DX[i];
			int y = yPos - DY[i];

			// out of bounds
			if (x < 0 || x >= r || y < 0 || y >= c) continue;

			// illegal
			if (grid[x][y] == '#') continue;

			// Go through the snake.
			boolean ok = true;
			int cur = 10*xPos + yPos;

			// To deal with special case of snake of length 2.
			int limit = (n == 2) ? 2 : n-1;

			// Check for self-intersection.
			for (int j=1; j<limit; j++) {
				cur += OFFSET[(dir >> (2*(n-1-j))) & 3];
				if (cur == 10*x+y) {
					ok = false;
					break;
				}
			}

			// Self-intersected.
			if (!ok) continue;

			// Add it!
			int newmask = ((10*x+y) << (2*n-2)) | (i << (2*n-4)) | (dir >> 2);
			if (n == 1) newmask = ((10*x+y) << (2*n-2));
			next.add(newmask);
		}

		// Here is the list.
		return next;
	}
}
