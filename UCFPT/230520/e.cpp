#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using ld = long double;

struct FT {
    vl s;
    FT(int n) : s(n) {}
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
        int n, k; cin >> n >> k;
        vi a(n);
        vi idx(n);
        FT ft(n + 5);
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
            idx[a[i]] = i;
            ft.update(i, 1);
        }
        int numsec = (n + k - 1) / k;
        ll s1 = 0, s2 = 0;
        rep(i, 0, numsec){
            ll cnt = min(k, n - k * i);
            vl ids, actids;
            rep(j, k * i, k * i + cnt){
                ids.pb(idx[j]);
                actids.pb(j);
            }
            sort(all(ids));
            ll swapsum = 0;
            rep(j, 0, cnt){
                swapsum += ft.query(ids[j] + 1) - 1 - j;
                s2 = max(s2, abs(ids[j] - actids[j]));
            }
            s1 += swapsum;
            rep(j, 0, cnt){
                ft.update(ids[j], -1);
            }
        }
        cout << "Case " << (cn + 1) << ": " << (s1 - s2) << "\n";
    }
}