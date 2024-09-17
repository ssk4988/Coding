#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

void solve() {
    int n, m; cin >> n >> m;
    vl a(n);
    ll ans = 0;
    map<ll, ll> freq;
    vl vs;
    rep(i, 0, n){
        cin >> a[i];
        freq[a[i]]++;
        vs.pb(a[i]);
    }
    sort(all(vs));
    vs.erase(unique(all(vs)), end(vs));
    vpl bad(m);

    vvi adj(sz(vs));
    rep(i, 0, m){
        cin >> bad[i].f >> bad[i].s;
        bad[i].f = lower_bound(all(vs), bad[i].f) - begin(vs);
        bad[i].s = lower_bound(all(vs), bad[i].s) - begin(vs);
        adj[bad[i].f].pb(bad[i].s);
        adj[bad[i].s].pb(bad[i].f);
    }
    vi cant(sz(vs));

    vi freqs;
    for(auto [key, val] : freq) {
        freqs.pb(val);
    }
    sort(all(freqs));
    freqs.erase(unique(all(freqs)), end(freqs));
    vector<vpl> buckets(sz(freqs));
    for(auto [arrv, f] : freq) {
        int idx = lower_bound(all(freqs), f) - begin(freqs);
        buckets[idx].push_back({arrv, lower_bound(all(vs), arrv) - begin(vs)});
    }
    rep(i, 0, sz(freqs)){
        sort(all(buckets[i]));
        reverse(all(buckets[i]));
    }
    rep(i, 0, sz(freqs)){
        for(auto [x, xidx] : buckets[i]){
            for(int yidx : adj[xidx]) cant[yidx] = true;
            rep(j, 0, sz(freqs)){
                for(auto [y, yidx] : buckets[j]) {
                    if(cant[yidx] || y == x) continue;
                    ans = max(ans, ll(freqs[i] + freqs[j]) * (x + y));
                    break;
                }
            }
            for(int yidx : adj[xidx]) cant[yidx] = false;
        }
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
