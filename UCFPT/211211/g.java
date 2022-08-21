import java.io.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int target = n - 3;
        int answer = target;
        for(int i = 1; i * i <= target; i++){
            if(answer < i) break;
            if(target % i == 0){
                if(i > 3 && i < answer){
                    answer = i;
                }
                int other = target / i;
                if(other > 3 && other < answer){
                    answer = other;
                }
            }
        }
        System.out.println(answer);
        

        in.close();
    }
}