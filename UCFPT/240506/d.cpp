#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vl a(n);
        priority_queue<ll, vl, greater<ll>> pq;
        rep(i, 0, n){
            cin >> a[i];
        }
        vii c(m);
        vvi bucket(n);
        rep(i,0,m){
            cin >> c[i].first >> c[i].second; c[i].first--;
            bucket[c[i].first].push_back(c[i].second);
        }
        rep(i, 0, n){
            pq.push(a[i]);
            for(auto d : bucket[i]){
                ll x = pq.top(); pq.pop();
                x -= d;
                pq.push(x);
            }
        }
        ll ans = 0;
        rep(i, 0, n){
            ll x = pq.top(); pq.pop();
            ans += x;
            cout << ans << " ";
        }
        cout << "\n";
    }
    return 0;
}
