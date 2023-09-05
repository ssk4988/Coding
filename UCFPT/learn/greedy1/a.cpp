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
        int n; cin >> n;
        
        priority_queue<ll, vl, greater<ll>> pq;
        rep(i, 0, n){
            ll k; cin >> k;
            pq.push(k);
        }
        ll score = 0;
        while(pq.size() > 1){
            ll k1 = pq.top(); pq.pop();
            ll k2 = pq.top(); pq.pop();
            score += k1 + k2;
            pq.push(k1 + k2);
        }
        cout << score << nL;

    }
    
    return 0;
}
