package solutions.thief;

import java.util.*;
import java.io.*;

public class thief{

	public static void main(String[] args) throws IOException{
		Scanner scan = new Scanner(System.in);
		int t = scan.nextInt();
		for(int q = 1; q <= t; q++){
			int n = scan.nextInt();
			int[] value = new int[n];
			for(int i = 0; i < n; i++) value[i] = scan.nextInt();

			// dp[i][j]: store the best answer when considering first i paintings. j = 1 if we used our bolt cutter, j = 0 otherwise
			int[][] dp = new int[n][2];
			for(int i = 0; i < n; i++){

				// Without using our bolt cutter:
				for(int j = 0; j < 2; j++){
					// We can get the painting at i, so our answer is at least this
					dp[i][j] = value[i];

					// We could try to pick up the best answer using the first i-2 painting and include ith painting
					if(i >= 2){
						dp[i][j] = Math.max(dp[i][j], value[i]+dp[i-2][j]);
					}

					// We can take the answer of the first i-1 paintings if it's better
					if(i >= 1){
						dp[i][j] = Math.max(dp[i][j], dp[i-1][j]);
					}
				}
				
				// Using a bolt cutter allows us to take answer of first i-2 paintings, and take the ith and (i-1)th paintings
				if(i >= 1)
					dp[i][1] = Math.max(dp[i][1], value[i]+value[i-1]);

				if(i >= 2)
					dp[i][1] = Math.max(dp[i][1], dp[i-2][0]+value[i]+value[i-1]);
			}
			
			System.out.println(dp[n-1][1]);
		}
		scan.close();
	}

}