package solutions.manhattan;

import java.util.*;
import java.io.*;
public class manhattan {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer t = new StringTokenizer(in.readLine());
		
		int n = Integer.parseInt(t.nextToken());
		
		for(int i = 0; i < n; i++) {
			t = new StringTokenizer(in.readLine());
			
			long x1 = Long.parseLong(t.nextToken());
			long y1 = Long.parseLong(t.nextToken());
			long x2 = Long.parseLong(t.nextToken());
			long y2 = Long.parseLong(t.nextToken());
			
			//if the two points can be connected with a straight line relative to the x or y axis
			//then Manhattan and Euclid will arrive at the same time
			//otherwise, Euclid will arive before Manhattan
			
			if(x1 == x2 || y1 == y2) {
				System.out.println("Dr. Manhattan wins again!");
			}
			else {
				System.out.println("Euclid is too fast!");
			}
			
		}
		
		in.close();
	}
}