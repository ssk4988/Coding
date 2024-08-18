#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ld = long double;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
using pll = pair<ll, ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    ll c; cin >> n >> c;
    vl t(n), d(n);
    ll left = 0;
    rep(i, 0, n){
        cin >> t[i] >> d[i];
        left += t[i];
    }
    ll curt = 0;
    priority_queue<pll> pq;
    ll diffsum1 = 0;
    ll diffsum = 0;
    priority_queue<pll, vector<pll>, greater<pll>> events;
    auto check = [&]() -> void {
        // cout << "check adds " << max(0LL, (-c + left - diffsum1) / diffsum - 1) << " to " << curt << " diffsum1 " << diffsum1 << " diffsum " << diffsum << endl;
        // if(diffsum == 0) return;
        // find min nex such that (left - diffsum1 - c) - diffsum * nex <= 0
        // (left - diffsum1 - c) <= diffsum * nex
        // ceil((left - diffsum1 - c) / diffsum) == nex
        ll nex = max(0LL, (-c + left - diffsum1 + diffsum - 1) / diffsum);
        // cout << "curt " << curt << " add " << nex << " to get " << (curt + nex) << endl;
        events.push({curt + nex, n});
    };
    auto add = [&]() -> void {
        if(pq.empty()) return;
        auto [k, idx] = pq.top(); pq.pop();
        diffsum1 += k - 1;
        diffsum += k;
        events.push({curt + t[idx] / k, idx});
    };
    rep(i, 0, n){
        pq.push({d[i], i});
    }
    rep(i, 0, min(c, ll(n))){
        add();
    }
    check();
    ll ans = 1e18;
    while(!events.empty()){
        auto [t1, idx] = events.top(); events.pop();
        // cout << "at time " << t1 << " event on " << idx << " ";
        ll pret = curt;
        curt = t1;
        left -= (curt - pret) * diffsum;
        // cout << " left is " << left << " diffsum is " << diffsum << " diffsum1 " << diffsum1 << endl;
        if(idx == n && left - diffsum1 <= c){
            ans = curt;
            break;
        }
        if(idx != n){
            t[idx] %= d[idx];
            diffsum -= d[idx];
            diffsum1 -= d[idx] - 1;
            ll nex = min(d[idx], t[idx]);
            d[idx] = nex;
            if(d[idx] != 0){
                pq.push({d[idx], idx});
            }
            add();
            check();
            events.push({curt, n});
        }
    }
    assert(ans != 1e18);
    cout << ans << "\n";
    return 0;
}
