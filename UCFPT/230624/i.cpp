#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

const bool DEBUG = false;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vl cnt(m);
    rep(i, 0, n){
        int v; cin >> v; v--;
        cnt[v]++;
    }
    auto tri = [](ll k)->ll{return k * (k + 1) / 2;};
    auto cost = [&](ll students, ll resets)->ll{
        resets++;
        if(resets >= students) return students;
        ll fl = students / resets;
        ll incs = students - fl * resets;
        ll res = tri(fl) * (resets - incs) + tri(fl + 1) * incs;
        return res;
    };
    ll lo = 0, hi = 0;
    rep(i, 0, m) hi = max(hi, cost(cnt[i], 0) - cost(cnt[i], 1));
    while(lo < hi){
        ll mid = lo + (hi - lo + 1) / 2;
        ll val = 0;
        rep(i, 0, m){
            ll lo1 = 0, hi1 = cnt[i] + 5;
            while(lo1 < hi1){
                ll mid1 = lo1 + (hi1 - lo1 + 1) / 2;
                if(cost(cnt[i], mid1 - 1) - cost(cnt[i], mid1) >= mid){
                    lo1 = mid1;
                } else hi1 = mid1 - 1;
            }
            val += lo1;
            if(DEBUG) cout << "for p=" << cnt[i] << ", derivative of " << mid << " yields " << lo1 << " resets" << "\n";
        }
        if(val >= k) lo = mid;
        else hi = mid - 1;
    }
    ll val = 0, total = 0;
    rep(i, 0, m){
        ll lo1 = 0, hi1 = cnt[i] + 5;
        while(lo1 < hi1){
            ll mid1 = lo1 + (hi1 - lo1 + 1) / 2;
            if(cost(cnt[i], mid1 - 1) - cost(cnt[i], mid1) >= lo){
                lo1 = mid1;
            } else hi1 = mid1 - 1;
        }
        val += lo1;
        total += cost(cnt[i], lo1);
    }
    total -= (lo) * (k - val);
    cout << total << "\n";
}
