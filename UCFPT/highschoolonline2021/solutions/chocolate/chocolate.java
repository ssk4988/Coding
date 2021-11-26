package solutions.chocolate;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class chocolate {

	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(System.in);
		int cases = scan.nextInt();
		while(cases-->0) {
			int n = scan.nextInt();
			int m = scan.nextInt();
			int[] start = new int[m];
			int[] end = new int[m];
			int[] start_freq = new int[n+2];
			for(int i = 0;i<m;i++) {
				start[i] = scan.nextInt();
				end[i] = scan.nextInt();
				start_freq[start[i]]++;
			}
			//solution is to as many intervals as possible, for example: merge (1,3)(4,5) into (1,5)
			
			//number of intervals at the start is m
			int ans = m;
			
			//Iterate through all interval ending points
			for(int i =0 ;i<m;i++) {
				if(start_freq[end[i]+1]>0) {
					//An interval starts right after this one ends, so we can merge the two
					ans--;
					start_freq[end[i]+1]--;
				}
			}
			System.out.println(ans);
		}
	}

}
