package solutions.banana;
import java.util.Scanner;

// 2021 UCF HSPT Online Edition - Banana Pancake Perfection
// Author: Natalie Longtin

/*
the number of bananas is less than 8, so it is sufficient to check
every possible mapping of bananas to target locations.
if we map banana 1 to location l1, banana 2 to location l2, etc,
this problem is equivalent to iterating over all permutations of the list l,
and determining the minimum total distance to push the bananas across each of these situations.
*/

public class banana {
	public static void main(String[] args) {
		Scanner scan=new Scanner(System.in);
		
		//process test cases
		int t=scan.nextInt();
		for(int tt=0;tt<t;tt++) {
			int n=scan.nextInt();
			bananas=new pt[n];
			targets=new pt[n];
			
			for(int i=0;i<n;i++) {
				bananas[i]=new pt(scan.nextInt(),scan.nextInt());
			}
			for(int i=0;i<n;i++) {
				targets[i]=new pt(scan.nextInt(),scan.nextInt());
			}
			res=Double.MAX_VALUE;
			
			//find and evaluate each permutation of integers 0 to n-1
			perm(new int[n],new boolean[n],0);
			System.out.println(res);
		}
		scan.close();
	}
	//given a possible permutation (mapping of bananas to locations),
	//calculate the sum of distances to push the bananas
	public static void eval(int[] perm) {
		double temp=0;
		for(int i=0;i<perm.length;i++) {
			temp+=bananas[i].dist(targets[perm[i]]);
		}
		//update the total distance if we have found a better answer
		res=Math.min(res,temp);
	}
	public static void perm(int[] perm, boolean[] v, int k) {
		//if we have filled in all numbers for this permutation, we must evaluate it
		if(k==perm.length) {
			eval(perm);
			return;
		}
		for(int i=0;i<v.length;i++) {
			//cannot have duplicates in a permutation
			if(v[i]) continue;
			
			//if we get here, we can use this number as our next element
			perm[k]=i;
			v[i]=true;
			perm(perm,v,k+1);
			
			//set v[i] to false once more so that it can be used elsewhere
			v[i]=false;
		}
	}
	static double res;
	static pt[] bananas,targets;
	static class pt {
		int x,y;
		pt(int x, int y) {
			this.x=x;
			this.y=y;
		}
		double dist(pt o) {
			return Math.sqrt((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y));
		}
	}
}