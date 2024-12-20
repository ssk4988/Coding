#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int reads(){
    string s; cin >> s;
    int v = 0;
    for(char c : s){
        v = v * 2 + (c == '1');
    }
    return v;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        int start = reads();
        vi rem(m), add(m), dur(m);
        rep(i, 0, m){
            cin >> dur[i];
            rem[i] = reads();
            add[i] = reads();
        }
        priority_queue<pii, vii, greater<>> q;
        const int inf = 2e9;
        vi d(1 << n, inf);
        q.push({0, start});
        while(sz(q)){
            auto [d_u, u] = q.top(); q.pop();
            if(d[u] != inf) continue;
            d[u] = d_u;
            rep(i, 0, m){
                int mask = u;
                mask &= ~rem[i];
                mask |= add[i];
                q.push({d[u]+dur[i], mask});
            }
        }
        if(d[0] == inf) d[0] = -1;
        cout << d[0] << "\n";
    }    
    
    return 0;
}
