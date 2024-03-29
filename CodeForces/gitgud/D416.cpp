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
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    int start = 0;
    int ans = 0;
    while(start < n){
        int cur = start;
        vpl seq;
        while(cur < n){
            if(sz(seq) == 0){
                if(a[cur] == -1){
                    // do nothing
                }
                else{
                    seq.pb({a[cur], cur});
                }
            }
            else if(sz(seq) == 1){
                if(a[cur] == -1){
                    // do nothing
                }
                else{
                    ll dif = (a[cur] - seq[0].f);
                    if(dif % (cur - seq[0].s) != 0) break;
                    dif /= cur - seq[0].s;
                    ll first = seq[0].f + dif * (start - seq[0].s);
                    if(first <= 0) break;
                    seq.pb({a[cur], cur});
                }
            }
            else{
                ll target = seq[0].f + (seq[1].f - seq[0].f) / (seq[1].s - seq[0].s) * (cur - seq[0].s);
                if(target <= 0) break;
                if(a[cur] != -1 && a[cur] != target) break;
            }
            cur++;
        }
        // cout << start << " " << cur << endl;
        ans++;
        start = cur;
    }
    cout << ans << "\n";
    
    return 0;
}
