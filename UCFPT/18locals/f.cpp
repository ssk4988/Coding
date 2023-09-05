#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n; cin >> n;
    vl divs = {2, 5, 1};
    vl ans;
    const ll lim = 1e18;
    auto dfs = [&](int idx, ll cur, auto &&dfs)->void{
        if(idx == 2){
            if(n % cur == 0) ans.pb(cur);
            return;
        }
        rep(i, idx, 3){
            if(cur * divs[i] > lim) continue;
            dfs(i, cur * divs[i], dfs);
        }
    };
    dfs(0, 1, dfs);
    sort(all(ans));
    cout << sz(ans) << "\n";
    for(ll i : ans) cout << i << "\n";
}
