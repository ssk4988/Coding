#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        string str; cin >> str;
        int curlevel = 0;
        int best = 0;
        for(int i = 0; i < str.size(); i++){
            if(str[i] == 'v') curlevel++;
            else if(str[i] == '^') curlevel--;
            best = max(best, curlevel);
        }
        cout << best << "\n";
    }
}
