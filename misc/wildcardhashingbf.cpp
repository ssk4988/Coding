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
    int n, q, k;
    ll b, m;
    cin >> n >> q >> k >> b >> m;
    vi s(n);
    rep(i, 0, n){
        string v; cin >> v;
        for(char c : v) s[i] = s[i] * 2 + (c - '0');
    }
    rep(i, 0, q){
        string pat; cin >> pat;
        int usemask = 0;
        int valmask = 0;
        for(char c : pat){
            usemask = usemask * 2 + (c != '*');
            valmask = valmask * 2 + (c == '1');
        }
        vi pos;
        rep(j, 0, n){
            if((s[j] & usemask) == valmask) {
                pos.pb(s[j]);
            }
        }
        sort(all(pos));
        ll ans = 0;
        for(int x : pos){
            ans = (ans * b + x) % m;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
