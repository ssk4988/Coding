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

bool query(int i, int j){
    cout << "? " << i+1 << " " << j+1 << endl;
    string res; cin >> res;
    return res == "YES";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc; 
    rep(cn, 0, nc){
        int n; cin >> n;
        vi par(n, -1);
        vvi src(3);
        src[0].pb(n-1);
        for(int i = n-2; i >= 0; i--){
            if(sz(src[2])){
                if(query(i, src[2].back())){
                    src[2].pb(i);
                    continue;
                }
                if(query(i, src[1].back())){
                    src[1].pb(i);
                    src[0].insert(end(src[0]), all(src[2]));
                } else{
                    src[0].pb(i);
                    src[1].insert(end(src[1]), all(src[2]));
                }
                src[2].clear();
            } else {
                bool b0 = query(i, src[0].back());
                if(sz(src[1]) == 0){
                    src[b0 ? 0 : 1].pb(i);
                } else {
                    bool b1 = query(i, src[1].back());
                    if(b0 && b1) src[2].pb(i);
                    else src[b0 ? 0 : 1].pb(i);
                }
            }
        }
        src[0].insert(end(src[0]), all(src[2]));
        vi ans(n);
        for(int i : src[1]) ans[i] = 1;
        cout << "! ";
        rep(i, 0, n) cout << ans[i] << " ";
        cout << endl;
    }
    
    return 0;
}
