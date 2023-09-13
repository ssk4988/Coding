#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n, s; cin >> n >> s;
        set<string> names;
        for(int i = 0; i < n; i++){
            string str; cin >> str;
            names.insert(str);
        }
        int time = -1;
        string winner;
        set<string> seen;
        for(int i = 0; i < s; i++){
            string str; cin >> str;
            seen.insert(str);
            if((int)seen.size() + 1 == n && time == -1){
                time = i + 1;
                for(string str : names){
                    if(seen.count(str) == 0) winner = str;
                }
            }
        }
        cout << winner << " " << time << "\n";
    }
}
