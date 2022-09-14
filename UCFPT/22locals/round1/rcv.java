import java.io.*;
import java.util.*;

public class rcv {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int c = 0;
        Map<String, Integer> m = new HashMap<>();
        ArrayList<String> rev = new ArrayList<>();
        Map<Integer, ArrayList<Integer>> votes = new HashMap<>();
        TreeSet<Integer> keys = new TreeSet<>();
        Map<Integer, Integer> ind = new HashMap<>();
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            String s = in.readLine();
            if (!m.containsKey(s)) {
                m.put(s, c++);
                rev.add(s);
            }
            v[i] = m.get(s);
        }
        boolean[] elim = new boolean[c];
        int[] cnt = new int[c];
        for (int i = 0; i < n; i++) {
            cnt[v[i]]++;
        }
        for (int i = 0; i < c; i++) {
            if (!votes.containsKey(cnt[i])) {
                votes.put(cnt[i], new ArrayList<>());
            }
            votes.get(cnt[i]).add(i);
            keys.add(cnt[i]);
        }
        int xyz = 0;
        for (int i : keys) {
            ind.put(xyz, i);
            xyz++;
        }
        int[] pref = new int[xyz];
        for(int i = 0; i < xyz; i++){
            pref[i] = votes.get(ind.get(i)).size() * ind.get(i);
            if(i>0)pref[i] += pref[i-1];
        }
        int majority = -1;
        for (int i = 0; i < c; i++) {
            if (2 * cnt[i] > n)
                majority = i;
        }
        if (majority > -1) {
            for (int i = 0; i < c; i++) {
                if (i == majority)
                    continue;
                elim[i] = true;
            }
        } else {
            int low = 0;
            int high = xyz;
            while(low < high){
                int mid = low + (high - low)/2;
                int left = mid > 0 ? pref[mid-1] : 0;
                left += ind.get(mid);
                boolean works = left > ind.get(mid);
                if(works){
                    left = pref[mid];
                    for(int i = mid+1; i < xyz && works; i++){
                        if(left > ind.get(i)){
                            left += pref[i]-pref[i-1];
                        }
                        else{
                            works = false;
                        }
                    }
                }
                if(works){
                    high = mid;
                }
                else{
                    low = mid + 1;
                }
            }
            for(int k = 0; k < low; k++){
                for(int l : votes.get(ind.get(k))){
                    elim[l]=true;
                }
            }
        }
        TreeSet<String> ans = new TreeSet<>();
        for (int i = 0; i < c; i++) {
            if (elim[i]) {
                ans.add(rev.get(i));
            }
        }
        System.out.println(ans.size());
        for (String s : ans) {
            System.out.println(s);
        }
        in.close();
    }
}