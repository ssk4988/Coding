#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n, m; ll k; cin >> n >> m >> k;

        vl a(k);
        rep(i, 0, k) cin >> a[i];
        sort(all(a));
        reverse(all(a));
        bool works = false;
        rep(_, 0, 2){
            ll ans = 0;
            ll add = 0;
            int used = 0;
            for(auto x : a){
                if(x / n >= 2){
                    if(ans + 2 <= m){
                        ans += 2;
                        add += x / n - 2;
                    }
                }
            }
            if(ans + add >= m) works = true;
            // if(m == 3 && a[0] / n < 3) continue;
            // if(ans >= m) works = true;
            swap(n, m);
        }
        cout << (works ? "Yes" : "No") << nL;
    }
    
    return 0;
}