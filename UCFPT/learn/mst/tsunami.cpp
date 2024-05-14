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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vii c(n);
        int mny = INT_MAX;
        rep(i, 0, n){
            cin >> c[i].f >> c[i].s;
            mny = min(mny, c[i].s);
        }
        priority_queue<tuple<int, ld, int>, vector<tuple<int, ld, int>>, greater<tuple<int, ld, int>>> pq;
        set<int> seen;
        auto relax = [&](int x) -> void {
            rep(i,0,n){
                if(c[i].s < c[x].s) continue;
                int dx = c[i].f - c[x].f, dy = c[i].s - c[x].s;
                ld d = sqrtl(dx * dx + dy * dy);
                pq.push({c[i].s, d, i});
            }
        };
        rep(i, 0, n){
            if(mny == c[i].s) {pq.push({c[i].s, 0, i}); break; }
        }
        ld ans = 0;
        while(!pq.empty()){
            auto [y, d, u] = pq.top(); pq.pop();
            if(seen.count(u)) continue;
            seen.insert(u);
            ans += d;
            relax(u);
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
