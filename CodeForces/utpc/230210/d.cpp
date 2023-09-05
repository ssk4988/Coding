#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, m; cin >> n >> m;
    ll last = m;
    ll req = last * (last + 1) / 2 - (last - m) * (last - m + 1) / 2;
    // cout << req << "\n";
    int pnt = 0;
    vl e(n);
    rep(i, 0, n) cin >> e[i];
    ll ans = 0;
    while(pnt < n){
        ll cur = 0;
        while(pnt < n && cur < req) cur += e[pnt++];
        if(cur >= req) ans++;
        last += m;
        req = last * (last + 1) / 2 - (last - m) * (last - m + 1) / 2;
        // cout << req << "\n";
    }
    cout << ans << "\n";
    
}
