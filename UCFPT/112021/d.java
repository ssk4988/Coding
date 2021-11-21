/*
ID: ssk49881
LANG: JAVA
TASK: d
*/

import java.io.*;
import java.util.*;
import java.util.regex.Pattern;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        String regex = "^\"[a-zA-Z ]+\" [a-zA-Z ]+$";

        String line = in.readLine();
        while (!line.equals("END")) {
            boolean works = Pattern.compile(regex).matcher(line).matches();
            String[] sarray = line.split("\"");
            if (works) {
                // System.out.println(Arrays.toString(sarray));
                String regex1 = "[a-zA-z ]+";

                if (works && sarray.length != 3)
                    works = false;
                if (works && sarray[0].length() != 0)
                    works = false;
                if (works && !sarray[2].substring(0, 1).equals(" "))
                    works = false;
                if (works)
                    sarray[2] = sarray[2].substring(1);
                if (works && !sarray[1].equals(sarray[2]))
                    works = false;
                if (works && !Pattern.compile(regex1).matcher(sarray[1]).matches())
                    works = false;
                if (works && (sarray[1].substring(0, 1).equals(" ")
                        || sarray[1].substring(sarray[1].length() - 1, sarray[1].length()).equals(" ")))
                    works = false;
            }

            if (!works) {
                System.out.println("not a quine");
            } else {
                System.out.println("Quine(" + sarray[1] + ")");
            }
            line = in.readLine();
        }

        in.close();
        out.close();
    }
}