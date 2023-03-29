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
    ll a, b; cin >> a >> b;
    vl v(n), pref(n);
    rep(i, 0, n){
        cin >> v[i];
        pref[i] += v[i];
        if(i > 0) pref[i] += pref[i - 1];
    }
    
    deque<pl> dq;
    dq.pb({0, -1});
    ll ans = LLONG_MIN;
    rep(i, a - 1, n){
        if(i - a >= 0){
            while(dq.size() > 0 && dq.back().f > pref[i - a]){
                dq.pop_back();
            }
            dq.push_back({pref[i - a], i - a});
        }
        if(dq.size() > 0){
            ans = max(pref[i] - dq.front().f, ans);
        }
        while(dq.size() > 0 && dq.front().s <= i - b){
            dq.pop_front();
        }
    }
    cout << ans << nL;

    
    return 0;
}
