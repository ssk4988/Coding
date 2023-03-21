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
    int n, k;cin >> n >> k;
    map<int, int> cur;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    ll ans = 0;
    int r = 0;
    rep(l, 0, n){
        while(r < n && (cur.size() < k || (cur.size() == k && cur.find(a[r]) != cur.end()))){
            cur[a[r]]++;
            r++;
        }
        ans += r - l;
        cur[a[l]]--;
        if(cur[a[l]] == 0){
            cur.erase(a[l]);
        }
    }
    cout << ans << nL;
    
    return 0;
}
