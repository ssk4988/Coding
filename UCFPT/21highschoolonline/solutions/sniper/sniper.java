package solutions.sniper;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class sniper {

	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(System.in);
		//idea for this solution is to maintain a prefix sum of the number of allies - number of enemies up to each index
		//then because we know how many targets each bullet hits from the left, we simply add to our answer the prefix sum we calculated for the number of targets
		//if we calculated that this bullet would heal more enemies than allies, we don't shoot it.
		int cases = scan.nextInt();
		for(int t = 0;t<cases;t++) {
			int n= scan.nextInt();
			int k = scan.nextInt();
			long hpAlly = 0;
			long hpEnemy = 0;
			long[] arr= new long[n];
			//keeps track of the difference in number of allies vs number of enemies up to each index
			long[] prefixDiff = new long[n];
			int diff = 0;
			for(int i =0;i<n;i++) {
				arr[i] =scan.nextLong();
				if(arr[i]<0) {
					hpEnemy+=arr[i];
					diff--;
				}else if (arr[i]>0){
					hpAlly+=arr[i];
					diff++;
				}
				prefixDiff[i] = diff;
			}
			
			long currDiff = (hpAlly+hpEnemy);
			int[] shot = new int[k];
			for(int i = 0;i<k;i++) {
				shot[i] = scan.nextInt();
				//skip this bullet if it hits more enemies than allies
				if(prefixDiff[shot[i]-1]<=0)continue;
				currDiff+=prefixDiff[shot[i]-1];
			}
			System.out.println(currDiff);
		}
	}

}
