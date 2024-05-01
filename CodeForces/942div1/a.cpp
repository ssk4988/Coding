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
        int n; ll k; cin >> n >> k;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        ll best = 0;
        auto test = [&](ll x) -> bool {
            ll cnt = 0;
            rep(i, 0, n){
                if(a[i] < x) cnt += x - a[i];
            }
            return cnt <= k;
        };
        for(ll dif = 1LL << 42; dif; dif /= 2){
            if(test(best + dif)) best += dif;
        }
        rep(i, 0, n){
            if(a[i] < best) k -= best - a[i];
        }
        rep(i, 0, n) if(a[i] > best) k++;
        ll seq = k + best * n;
        cout << (seq - n + 1) << "\n";
    }
    
    return 0;
}
