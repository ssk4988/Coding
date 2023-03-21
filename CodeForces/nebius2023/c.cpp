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
        ll n, x, p; cin >> n >> x >> p;
        ll target = (n - x) % n;
        vl modvals(n + 1); // ignore index 0
        rep(i, 1, n + 1){
            modvals[i] = (modvals[i - 1] + i) % n;
        }
        ll modshift = (n % 2 == 0) ? n / 2 : 0;
        ll maxcheck = 0;
        if(n % 2 == 0){
            maxcheck = min(2 * n, p);
        }
        else{
            maxcheck = min(n, p);
        }
        set<ll> valid;
        ll curm = 0;
        rep(i, 1, maxcheck + 1){
            curm = (curm + i) % n;
            valid.insert(curm);
        }
        if(valid.find(target) != valid.end()){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
    
    return 0;
}
