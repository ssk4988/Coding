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
        int n, v;
        cin >> n >> v;
        ld n1 = n;
        vector<ld> prob(n + 1, 0);
        vector<ld> pref(n + 1, 0);
        prob[0] = pref[0] = 100;
        for(int i = 1; i <= n; i++){
            prob[i] = pref[i - 1] / n1;
            pref[i] = prob[i] + pref[i - 1];
        }
        rep(i, 0, v){
            int k; cin >> k;
            cout << prob[k] << nL;
        }
    }
    
    return 0;
}