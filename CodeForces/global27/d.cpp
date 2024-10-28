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

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        vl c(n);
        vl p(n);
        vl cont(n);
        rep(i, 0, n){
            cin >> a[i];
            c[i] = a[i];
            while(c[i] % 2 == 0){
                c[i] /= 2;
                p[i]++;
            }
        }
        // true if j is at least as good as i
        auto cmp = [&](int i, int j) -> bool {
            ll v = c[j];
            if(v >= c[i]) return true;
            rep(_, 0, p[j]){
                v *= 2;
                if(v >= c[i]) return true;
            }
            return false;
        };
        vi st;
        ll ans = 0;
        vl res(n);
        rep(i, 0, n){
            // cout << i << " " << c[i] << " " << p[i] << " ";
            cont[i] = c[i];
            while(sz(st)) {
                int prv = st.back();
                if(!cmp(prv, i)){
                    break;
                }
                st.pop_back();
                (ans = ans - cont[prv] + MOD) %= MOD;
                (ans += c[prv]) %= MOD;
                p[i] += p[prv];
                p[prv] = 0;
            }
            cont[i] = (c[i] * modpow(2, p[i])) % MOD;
            (ans += cont[i]) %= MOD;
            st.push_back(i);
            // cout << "newp: " << p[i] << " st: " << sz(st) << endl;
            res[i] = ans;
        }
        for(auto x : res)
            cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}
