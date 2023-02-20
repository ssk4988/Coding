import java.util.Scanner;

// Editorial:
//     Let's first examine a simpler version of the task. What if Steve doesn't have to start 
//     from the beginning every time that he fails a task? Let E(i) be the expected time to
//     complete task i. Also let t(i) be the time to complete task i and let p(i) be the
//     probability of completing task i. Each task can be represented by a Bernoulli trial 
//     (this means that it has only two possible outcomes - success and failure - and the 
//     probability of a specific outcome is fixed). The geometric distribution models the 
//     probability of needing k Bernoulli trials to obtain the first success. The mean of 
//     the geometric distribution represents the average number of trials to achieve the 
//     first success and is equal to 1 / p, where p is the probability of success. This tells 
//     us that we can expect 1 / p(i) attempts to achieve success on task i. The expected time 
//     to complete task i is the number of expected attempts multiplied by the time needed to 
//     attempt task i, yielding the formula E(i) = t(i) / p(i). The answer for this version of 
//     the problem is the sum of E(i) over all tasks. If you want an explanation of why this 
//     sum is the answer, check out https://brilliant.org/wiki/linearity-of-expectation/

//     How do we extend this to the actual problem, where Steve has to start over from the first 
//     task if he fails? We redefine E(i) to be the expected time to finish task i and all tasks 
//     before it. E(0) is still t(0) / p(0) but every other task requires a modified formula. 
//     The expected number of attempts to complete task i is still 1 / p(i) and the time taken 
//     to complete task i is still t(i), but we can no longer attempt task i without first getting 
//     through all of the previous tasks. The time taken to attempt task i is effectively 
//     t(i) + E(i - 1) because we have to pass previous tasks to even attempt it. Therefore,
//     E(i) = (t(i) + E(i - 1)) / p(i). Because of how we redefined E(i), the answer is now E(n - 1) 
//     (0-indexed) and it suffices to calculate E(i) in order.

public class uhc {
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);

        // read in input
        int n = scan.nextInt();
        double[] p = new double[n];
        int[] t = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = scan.nextDouble();
        }
        for (int i = 0; i < n; i++) {
            t[i] = scan.nextInt();
        }

        // e[i] represents the expected time to get past a task (including previous tasks)
        double[] e = new double[n];
        // calculate e(0)
        e[0] = t[0] / p[0];
        for (int i = 1; i < n; i++) {
            // calculate e(i) based on e(i - 1) and the formula from the editorial
            e[i] = (e[i - 1] + t[i]) / p[i];
        }
        System.out.println(e[n - 1]);
        scan.close();
    }
}
