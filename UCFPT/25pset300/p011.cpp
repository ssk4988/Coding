#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, c, p, q; cin >> n >> c >> p >> q;
    string s; cin >> s;
    vl pref(n+1);
    rep(i, 0, n){
        pref[i+1] = pref[i] + (s[i] == 'Y');
    }
    int rem = 0, cut = 0;
    set<pair<ll, ll>> ss;
    int ans = 0;
    auto getscore = [&](int i) -> ll{
        return p * i - pref[i] * q;
    };
    rep(i, 0, n+1) {
        ll score = getscore(i);
        while(rem < cut) {
            ss.erase({getscore(rem), -rem});
            rem++;
        }
        if(i - c >= cut) {
            ss.insert({getscore(i - c), -(i - c)});
            // cout << "add " << i-c << " " << getscore(i-c) << " to set at time " << i << endl;
        }
        if(sz(ss)) {
            auto [mn, mnidx] = *ss.rbegin();
            mnidx = -mnidx;
            // cout << "at " << i << " mn element is " << mn << ", " << mnidx << endl;
            if(mn >= score) {
                // cout << "use section " << mnidx << " " << i << endl;
                ans++;
                ss.erase(prev(ss.end()));
                cut = i;
            }
        }
    }
    cout << ans << "\n";

    return 0;
}

/*
add 0 0 to set at time 3
at 3 mn element is 0, 3
add 1 -1 to set at time 4
at 4 mn element is 0, 3
add 2 1 to set at time 5
at 5 mn element is 1, 5
use section 5 5
at 6 mn element is 0, 3
use section 3 6
at 7 mn element is -1, 4
use section 4 7
3
*/