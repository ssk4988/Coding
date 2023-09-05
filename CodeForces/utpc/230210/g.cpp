#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
// using pi = pair<int, int>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, e; cin >> n >> e;
    int ans = 0;
    ld pi = acosl(-1);
    vector<ld> rs;
    rep(i, 0, n){
        ld r, k; cin >> r >> k;
        if(k < pi){
            ans++;
            // cout << "auto escape " << i << "\n";
            continue;
        }
        ld e1 = r/k;

        // cout << "can escape " << i << " with energy " << e1 << " " << (pi * k / r) << "\n";
        if((r - e1) * k < pi * r){
            rs.push_back(ceill(e1));
        }
    }
    sort(all(rs));
    ld eleft = e;
    for(auto r : rs){
        if(r <= eleft){
            ans++;
            eleft -= r;
        }
    }
    cout << ans << "\n";
    
}
