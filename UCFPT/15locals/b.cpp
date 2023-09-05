#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        vi usa(3), russia(3);
        rep(i, 0, 3) cin >> usa[i];
        rep(i, 0, 3) cin >> russia[i];
        bool count = usa[0] + usa[1] + usa[2] > russia[0] + russia[1] + russia[2];
        bool medal = usa > russia;
        cout << usa[0] << " " << usa[1] << " " << usa[2] << " " << russia[0] << " " << russia[1] << " " << russia[2] << "\n";
        if(medal && count) cout << "both\n";
        else if(medal) cout << "color\n";
        else if(count) cout << "count\n";
        else cout << "none\n";
        cout << "\n";
    }
}
