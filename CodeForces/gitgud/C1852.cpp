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
        int n; ll k; cin >> n >> k;
        vi a(n);
        ll pos = 0;
        ll ans = 0;
        priority_queue<int, vi, greater<int>> pq;
        auto mod = [&](ll x) -> ll {
            return (x % k + k) % k;
        };
        ll pre = 0;
        rep(i, 0, n){
            cin >> a[i];
            a[i] %= k;
            int ascent = mod(a[i] - pos);
            int descent = mod(pos - a[i]);
            // if(a[i] > pre){
            //     pq.push(a[i] - pre);
            //     ans += pq.top(); pq.pop();

            // }
            if(pos % k == a[i]){
                // do nothing
            }
            else if(pos > a[i]){
                // can descend
                pq.push(ascent);
                pos -= descent;
            }
            else{
                if(sz(pq)){
                    int ascent1 = pq.top();
                    if(ascent1 < ascent){
                        ans += ascent1;
                        pq.pop();
                        pq.push(ascent);
                    }
                    else{
                        ans += ascent;
                    }
                }
                else{
                    ans += ascent;
                }
                pos += ascent;
            }
            pre = a[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
