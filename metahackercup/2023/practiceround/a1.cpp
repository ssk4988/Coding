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
        int s, d, k; cin >> s >> d >> k;
        int buns = 2 * (s + d);
        int burgers = s + 2 * d;
        int cheese = s + 2 * d;
        int reqbuns = k + 1;
        int reqburgers = k, reqcheese = k;
        cout << "Case #" << (cn + 1) << ": " << (buns >= reqbuns && burgers >= reqburgers && cheese >= reqcheese ? "YES" : "NO") << nL;
    }
    
    return 0;
}