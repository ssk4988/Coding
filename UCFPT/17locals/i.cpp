#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = long double;
using vvi = vector<vi>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define pb push_back
#define f first
#define s second

struct FT{
    vector<ll> s;
    FT(int n) : s(n){}
    void update(int pos, ll dif){
        for(; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos){
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n), rev(n);
        set<int> active;
        FT ft(n);
        ll totsum = 0;
        rep(i, 0, n){
            cin >> a[i]; a[i]--;
            rev[a[i]] = i;
            totsum += a[i] + 1;
            ft.update(i, a[i] + 1);
            active.insert(i);
        }
        int top = 0;
        ll ans = 0;
        rep(i, 0, n){
            int r = rev[i];
            ll c1 = ft.query(max(top, r));
            if(min(top, r)) c1 -= ft.query(min(top, r));
            ll c2 = ft.query(n) - c1;
            // cout << min(top, r) << " to " << max(top, r) << ": " << c1 << " other: " << c2 << "\n";
            // if(top == r){

            // }
            ans += min(c1, c2);
            active.erase(r);
            ft.update(r, -i-1);
            if(sz(active)){
                auto it = active.lower_bound(r);
                if(it == active.end()) top = *active.begin();
                else top = *it;
            }
        }
        cout << ans << "\n";
    }
}
