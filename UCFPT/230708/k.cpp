#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;
using vvi = vector<vi>;
#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl c(n);
    rep(i, 0, n) cin >> c[i];
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi subsz(n, 1);
    vl duration(n), last(n);
    auto solve = [&](int cur, int par, auto &&solve)->void{
        vector<vl> child;
        last[cur] = c[cur];
        for(int nex : adj[cur]){
            if(nex == par) continue;
            solve(nex, cur, solve);
            duration[nex] += 2;
            subsz[cur] += subsz[nex];
            duration[cur] += duration[nex];
            last[nex] += 1;
            child.pb({last[nex] - duration[nex], nex});
        }
        sort(all(child));
        reverse(all(child));
        // duration[cur] = 2 * (subsz[cur] - 1);
        ll t = 0;
        rep(i, 0, sz(child)){
            last[cur] = max(last[cur], t + last[child[i][1]]);
            t += duration[child[i][1]];
        }
    };
    solve(0, -1, solve);
    ll ans = max(last[0], 2 * (n - 1) + c[0]);
    cout << ans << "\n";
}
