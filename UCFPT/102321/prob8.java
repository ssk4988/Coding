/*
ID: ssk49881
LANG: JAVA
TASK: prob8
*/

import java.io.*;
import java.util.*;

public class prob8 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        while(!(line = in.readLine()).equals("0")){
            StringTokenizer tokenizer = new StringTokenizer(line);
            int maxTime = Integer.parseInt(tokenizer.nextToken());
            if(!tokenizer.hasMoreTokens()){
                break;
            }
            int numJobType = Integer.parseInt(tokenizer.nextToken());
            int[] jobNum = new int[numJobType];
            int[] jobTime = new int[numJobType];
            Job[] jobs = new Job[numJobType];
            for(int i = 0; i < numJobType; i++){
                jobNum[i] = Integer.parseInt(tokenizer.nextToken().replace("(", "").replace(",", ""));
                jobTime[i] = Integer.parseInt(tokenizer.nextToken().replace(")", ""));
                jobs[i] = new Job(jobNum[i], jobTime[i]);
            }
            Arrays.sort(jobs);
            int time = 0;
            int numJobs = 0;
            int jindex = 0;
            while(time < maxTime && jindex < jobs.length){
                int addjob = Math.min((maxTime - time) / jobs[jindex].time, jobs[jindex].num);
                numJobs += addjob;
                time += jobs[jindex].time * addjob;
                jindex++;
            }
            System.out.println(numJobs + " " + time);
            int[][][] jobsFinished = new int[1][1][1];
        }
        in.close();
        out.close();
    }
    public static class Job implements Comparable<Job>{
        int num;
        int time;
        public Job(int num, int time){
            this.num = num;
            this.time = time;
        }
        @Override
        public int compareTo(prob8.Job o) {
            return this.time - o.time;
        }
    }
}