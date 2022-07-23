package solutions.maze;

import java.util.ArrayDeque;
import java.util.Scanner;

public class maze {
	static char[][] board;
	static int n, m;
	static int[] dr = {1,-1,0,0,0};
	static int[] dc = {0,0,1,-1,0};
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int cases =scan.nextInt();
		outer:while(cases-->0) {
			n = scan.nextInt();
			m = scan.nextInt();
			board =new char[n][m];
			boolean[][][] v = new boolean[n][m][9];
			for(int i = 0;i<n;i++) {
				board[i] = scan.next().toCharArray();
			}
			ArrayDeque<Point> deq = new ArrayDeque<>();
			for(int i = 0;i<n;i++) {
				for(int j = 0;j<m;j++) {
					if(i==0 || j==0 || i==n-1 || j==m-1) {
						//Can enter here, ground floor, unless there is a special tile/ adjacent gas
						if(!checkGas(i,j) || "EFP".contains(board[i][j]+"") || board[i][j]!='1')continue;
						deq.add(new Point(i,j,0));
						v[i][j][0] = true;
					}
				}
			}
			while(!deq.isEmpty()) {
				Point curr = deq.poll();
				if(board[curr.r][curr.c]=='*') {
					//Mario ya did it!
					System.out.println("You've got this!");
					continue outer;
				}
				for(int i =0;i<4;i++) {
					int tor = curr.r+dr[i];
					int toc = curr.c+dc[i];
					int goingToLevel = 0;
					//Make sure we are not traveling out of bounds or to a cell adjacent to gas.
					if(inBoinds(tor,toc) && checkGas(tor,toc)) {
						if("EFPG".contains(board[tor][toc]+"")) {
							goingToLevel = curr.story;
						}
						else if(board[tor][toc]=='*') {
							//Princess is at the highest story, 0 indexed;
							goingToLevel = 8;
						}else {
							//Convert the char value to an integer, 0 indexed;
							goingToLevel = board[tor][toc]-'0'-1;
						}
						//Note that no two adjacent spaces contain one of the 4 special spaces(E,F,P,G)
						if(board[curr.r][curr.c]=='E') {
							//Elevators allow us to travel between any of the adjacent rooms.
							if(!v[tor][toc][goingToLevel]) {
								v[tor][toc][goingToLevel] = true;
								deq.add(new Point(tor,toc,goingToLevel));
							}
						}else if(board[curr.r][curr.c]=='F') {
							//Fans allow us to travel to an adjacent room that is strictly higher than the current.
							if(goingToLevel>curr.story) {
								if(!v[tor][toc][goingToLevel]) {
									v[tor][toc][goingToLevel] = true;
									deq.add(new Point(tor,toc,goingToLevel));
								}
							}
						}else if(board[curr.r][curr.c]=='P') {
							//Poles allow us to travel to an adjacent room that is strictly lower than the current.
							if(goingToLevel<curr.story) {
								if(!v[tor][toc][goingToLevel]) {
									v[tor][toc][goingToLevel] = true;
									deq.add(new Point(tor,toc,goingToLevel));
								}
							}
						}else {
							//We can walk to an adjacent room that is at the same level, or one level higher or lower.
							if(curr.story+1>=goingToLevel && curr.story-1<=goingToLevel) {
								if(!v[tor][toc][goingToLevel]) {
									v[tor][toc][goingToLevel] = true;
									deq.add(new Point(tor,toc,goingToLevel));
								}
							}
						}
					}
				}
			}
			System.out.println("Find another way");
		}
	}
	static boolean inBoinds(int r, int c) {
		//Returns true if the point is within the bounds of the board
		return (r>=0 && c>=0 && r<n && c<m);
	}
	static boolean checkGas(int r, int c) {
		//Returns true if there is no gas adjacent to this point.
		for(int i = 0;i<5;i++) {
			int tor = r+dr[i];
			int toc = c+dc[i];
			if(inBoinds(tor,toc)) {
				if(board[tor][toc] == 'G')return false;
			}
		}
		return true;
	}
	static class Point{
		int r, c, story;
		public Point(int r, int c, int story) {
			this.r = r;
			this.c = c;
			this.story = story;
		}
	}
}
