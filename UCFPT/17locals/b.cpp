#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;

#define sz(x) (int)x.size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        string str1, str2; cin >> str1 >> str2;
        if(sz(str1) != sz(str2)){
            cout << "3\n";
            continue;
        }
        if(str1 == str2){
            cout << "1\n";
            continue;
        }
        bool issimilar = true;
        for(int i = 0; i < sz(str1); i++){
            int c1 = str1[i] - 'a', c2 = str2[i] - 'a';
            int r1 = c1 / 9, r2 = c2 / 9;
            c1 %= 9;
            c2 %= 9;
            if(abs(r1 - r2) > 1 || abs(c1 - c2) > 1){
                issimilar = false;
            }
        }
        if(issimilar){
            cout << "2\n";
        }
        else cout << "3\n";
    }
}
