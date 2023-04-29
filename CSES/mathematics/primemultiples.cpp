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
    ll n; int k; cin >> n >> k;
    vl p(k);
    rep(i, 0, k){
        cin >> p[i];
    }
    ll sum = 0;
    rep(i, 1, 1 << k){
        ll prod = 1;
        int parity = 0;
        rep(j, 0, k){
            if(i >> j & 1){
                if(n / prod < p[j]) prod = n + 1;
                else prod *= p[j];
                parity ^= 1;
            }
        }
        sum += (parity ? 1 : -1) * n / prod;
    }
    cout << (sum) << nL;
    
    return 0;
}