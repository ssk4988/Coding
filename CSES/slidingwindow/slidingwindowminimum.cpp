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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    ll x, a, b, c; cin >> x >> a >> b >> c;
    vi v;
    v.pb(x);
    rep(i, 0, n-1) {
        v.pb((a * v.back() + b) % c);
    }
    ll ans = 0;
    deque<pii> q;
    rep(i, 0, n) {
        while(sz(q) && q.back().f >= v[i]) q.pop_back();
        q.push_back({v[i], i});
        if(i >= k && q.front().s == i-k) q.pop_front();
        if(i >= k-1) ans ^= q.front().f;
    }
    cout << ans << "\n";
    
    return 0;
}
