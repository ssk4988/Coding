import java.util.*;
import java.io.*;

public class diskspace {
    public static final int[] days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    public static int currDay = 0;
    public static int[] prefdays;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();

        int length = Integer.parseInt(in.readLine());
        prefdays = new int[2020];
        for(int i = 1; i < prefdays.length; i++){
            prefdays[i] = prefdays[i-1] + 365;
            if(isLeap(i-1)) prefdays[i]++;
        }
        currDay = prefdays[2019] + days[0] + days[1] + days[2] + 27;
        for (int i = 0; i < length; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numFiles = Integer.parseInt(tokenizer.nextToken());
            double limit = Double.parseDouble(tokenizer.nextToken()) * 1000;
            ArrayList<Files> files = new ArrayList<>();
            for (int j = 0; j < numFiles; j++) {
                tokenizer = new StringTokenizer(in.readLine());
                String tyear = tokenizer.nextToken();
                tokenizer.nextToken();
                boolean ttime = (tokenizer.nextToken().equals("AM"));
                double tsize = Double.parseDouble(tokenizer.nextToken()) / 1000;
                String tname = tokenizer.nextToken();
                files.add(new Files(tyear, ttime, tsize, tname));
            }
            for (Files a : files) {
                a.calcScore();
            }
            Collections.sort(files);
            double storage = 0;
            for (int j = 0; j < files.size() && 4 * storage < limit; j++) {
                Files f = files.get(j);
                b.append(f.name + " " + String.format("%.3f", f.score) + "\n");
                storage += f.size;
            }

        }

        System.out.print(b);
        in.close();
    }

    public static class Files implements Comparable<Files> {
        public String date, name;
        public boolean time;
        public double size;
        public double score;

        public Files(String date, boolean time, double size, String name) {
            this.date = date;
            this.time = time;
            this.size = size;
            this.name = name;
        }

        public void calcScore() {
            int day = Integer.parseInt(date.split("/")[0]);
            int month = Integer.parseInt(date.split("/")[1]);
            int year = Integer.parseInt(date.split("/")[2]);

            double dayDiff = prefdays[year];
            for(int i = 0; i < month - 1; i++){
                dayDiff += days[i];
            }
            dayDiff += day;
            if(month > 2 && isLeap(year)) dayDiff++;
            if(!time) dayDiff += 0.5;

            this.score = this.size * (currDay - dayDiff);
        }

        @Override
        public int compareTo(diskspace.Files o) {
            if(this.score > o.score) return -1;
            if(this.score < o.score) return 1;
            return 0;
        }
    }
    public static boolean isLeap(int year){
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }
    public static int leap(int year){
        int val = year / 4 - year/100 + year /400;
        return val;
    }
}