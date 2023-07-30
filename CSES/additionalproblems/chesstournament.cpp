#include <bits/stdc++.h>
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
    vi x(n);
    vpi ans;
    bool possible = true;
    priority_queue<pi> pq;
    rep(i, 0, n){
        cin >> x[i];
        if(x[i]) pq.push({x[i], i + 1});
    }
    while(pq.size()){
        auto [d, a] = pq.top(); pq.pop();
        if(sz(pq) < d){
            possible = false;
            break;
        }
        vpi reinsert;
        rep(i, 0, d){
            auto [d1, b] = pq.top(); pq.pop();
            d1--;
            if(d1) reinsert.pb({d1, b});
            ans.pb({a, b});
        }
        for(auto &p : reinsert) pq.push(p);
    }
    if(!possible){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    cout << sz(ans) << nL;
    for(auto [a, b] : ans) cout << a << " " << b << nL;
    
    return 0;
}