#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const ll MOD = 1e9+7;

pair<ll, vl> redcnt(ll start, vl &a, int iter) {
    ll start1 = (start + start + a[1]) % MOD;
    priority_queue<pll, vll, greater<>> pq;
    rep(i, 0, sz(a)-1){
        pq.push({a[i] + a[i+1] - a[1], i+1});
    }
    vl a1;
    rep(i, 0, iter){
        auto [sm, idx] = pq.top(); pq.pop();
        a1.pb(sm);
        if(idx + 1 < sz(a)) pq.push({sm - a[idx] + a[idx+1], idx+1});
    }
    return{start1, a1};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll start = 0;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    start = a[0];
    rep(i,0,n) a[i] -= start;
    a.resize(min(64, n));
    rep(i, 0, n-64){
        tie(start, a) = redcnt(start, a, 64);
    }
    while(sz(a) > 1){
        tie(start, a) = redcnt(start, a, sz(a)-1);
    }
    cout << start << "\n";

    
    return 0;
}
