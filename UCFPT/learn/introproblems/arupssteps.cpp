#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int nc; cin >> nc;
    // for(int cn = 0; cn < nc; cn++){
        ll n; cin >> n;
        vector<vector<ll>> a(26, vector<ll>(26));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> a[i][j];
            }
        }
        ll q; cin >> q;
        for(int i = 0; i < q; i++){
            string str; cin >> str;
            ll ans = 0;
            for(int j = 1; j < (int)str.size(); j++){
                ans += a[str[j - 1] - 'A'][str[j] - 'A'];
            }
            cout << ans << "\n";
        }

    // }
}
