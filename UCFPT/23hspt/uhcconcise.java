import java.util.Scanner;
public class uhcconcise {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        double[] p = new double[n + 1];
        for (int i = 0; i < n; i++) p[i] = in.nextDouble();
        for (int i = 0; i < n; i++) p[n] = (p[n] + in.nextInt()) / p[i];
        System.out.println(p[n]);
    }
}
