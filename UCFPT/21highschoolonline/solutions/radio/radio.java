package solutions.radio;

import java.util.*;
import java.io.*;

public class radio{

	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int t = scan.nextInt();
		for(int q = 1; q <= t; q++){
			int n = scan.nextInt();
			int p = scan.nextInt();
			int s = scan.nextInt();
			String[] freq = new String[n];
			HashMap<String, Integer> map = new HashMap<String, Integer>();
			boolean[] preset = new boolean[n];
			for(int i = 0; i < n; i++){
				freq[i] = scan.next();
				map.put(freq[i], i);
			}
			for(int i = 0; i < p; i++){
				int x = map.get(scan.next());
				preset[x] = true;
			}

			
			// Calculate the distance from each frequency to a preset frequency
			// Cyclic distance can be computed as min(b-a, n-b+a), if a < b
			int[] distFromPreset = new int[n];
			Arrays.fill(distFromPreset, Integer.MAX_VALUE/2);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					int a = i;
					int b = j;
					if(b < a){
						int temp = a;
						a = b;
						b = temp;
					}
					if(preset[j]) distFromPreset[i] = Math.min(distFromPreset[i], Math.min(b-a, n-b+a));
				}
			}
			
			// For our answer, we either go to the closest preset to the destination frequency
			// or we go directly there. We take the shorter of the two options.
			System.out.println("Day #"+q+":");
			for(int i = 0; i < s; i++){
				int a = map.get(scan.next());
				int b = map.get(scan.next());
				
				int x = distFromPreset[b]+1;
				if(b < a){
					int temp = b;
					b = a;
					a = temp;
				}
				x = Math.min(x, Math.min(b-a, n-b+a));
				System.out.println(x);
			}
			System.out.println();
		}
	}
}
