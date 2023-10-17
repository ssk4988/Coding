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
    int n; cin >> n;
    int LIM = 2e6 + 100;
    set<int> ss;
    vi x(n);
    rep(i, 0, LIM){
        ss.insert(i);
    }
    rep(i, 0, n){
        cin >> x[i];
        ss.erase(x[i]);
    }
    int q; cin >> q;
    rep(i, 0, q){
        int idx; cin >> idx; idx--;
        int v = *ss.upper_bound(x[idx]);
        ss.insert(x[idx]);
        x[idx] = v;
        ss.erase(x[idx]);
        cout << v << nL;
    }
    
    return 0;
}
