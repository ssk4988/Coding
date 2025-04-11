#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if(sum <= 0) return -1;
        int pos = 0;
        for(int pw = 1 << 25; pw; pw >>= 1) {
            if(pos + pw <= sz(s) && s[pos+pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi p(n);
    FT ft(n), sft(n);
    ll ans = 0;
    rep(i, 0, n){
        cin >> p[i]; p[i]--;
        ll cnt = ft.query(n)-ft.query(p[i]);
        ll sm = sft.query(n)-sft.query(p[i]);
        ans += cnt * (p[i]+1);
        ans += sm;
        ft.update(p[i], 1);
        sft.update(p[i], p[i]+1);
    }
    cout << ans << "\n";
    return 0;
}
