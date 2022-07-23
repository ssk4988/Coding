package solutions.arithmetic;

import java.util.Scanner;

// 2021 UCF HSPT Online Edition - Arithmetic Sequence
// Author: Natalie Longtin

/*
the sum of elements in an arithmetic sequence is equal to the average of the first and last terms
multiplied by the number of terms. for a sequence of n terms, call the first term a. then the last term
will be equal to a+(n-1)d where d is the common difference between each term.

therefore, [a+(a+(n-1)d)]*n/2 = s
with algebraic manipulation, this reduces to:
(n-1)d = 2s/n - 2a

we demonstrate by casework that an answer exists iff (2s)%n = 0.
if 2s/n is even, the simplest solution is letting d=0 and a=s/n.

otherwise, we set d=1 and obtain:
n-1 = 2s/n - 2a
n must be even here because the fact that 2s/n is odd indicates that n must have divided out all the factors of 2.
therefore n-1 is odd.
2s/n we also know is odd, therefore 2a is even and no contradictions are possible.
*/

public class arithmetic {
	public static void main(String[] args) {
		Scanner scan=new Scanner(System.in);
		
		//process test cases
		int t=scan.nextInt();
		for(int tt=0;tt<t;tt++) {
			int n=scan.nextInt(), s=scan.nextInt();
			if((2*s)%n!=0) {
				System.out.print("IMPOSSIBLE");
			}
			else if(((2*s)/n)%2==0) {
				int term=s/n;
				for(int i=0;i<n;i++) System.out.print(term+" ");
			}
			else {
				int a=((2*s)/n-(n-1))/2;
				for(int term=a;term<a+n;term++) System.out.print(term+" ");
			}
			System.out.println();
		}
		scan.close();
	}
}
