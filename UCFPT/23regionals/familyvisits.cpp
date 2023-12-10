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
    int n, d; cin >> n >> d;
    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i] >> b[i];
    multiset<int> cleaning;
    int pre = 0;
    bool works = true;
    int ans = 0;
    rep(i, 0, d){
        int v; cin >> v;
        cleaning.clear();
        int mess = 0;
        rep(j, pre, v) mess += a[j];
        for(int cur = v - 1; cur >= pre; cur--){
            while(sz(cleaning) && *cleaning.begin() + mess <= b[cur]){
                mess += *cleaning.begin();
                cleaning.erase(cleaning.begin());
            }
            int rem = min(b[cur], mess);
            mess -= rem;
            cleaning.insert(rem);
        }
        if(mess > 0) works = false;
        ans += sz(cleaning);
        cout << sz(cleaning) << nL;
        pre = v;
    }
    cout << (works ? ans : -1) << nL;
    
    return 0;
}
