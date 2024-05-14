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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int cn = 0;
    while(true){
        int n, m; cin >> n >> m;
        if(n == 0) break;
        map<string, map<string, int>> d;
        set<string> nm;
        rep(i, 0, m){
            string a, b; cin >> a >> b;
            d[a][b] = d[b][a] = 1;
            nm.insert(a), nm.insert(b);
            d[a][a] = d[b][b] = 0;
        }
        {
            string s = "a";
            while(sz(nm) < n){
                nm.insert(s);
                s += 'a';
            }
        }
        const int oo = 1e9;
        for(auto &k : nm){
            for(auto &i : nm){
                for(auto &j : nm){
                    if(!d[i].count(j)) d[i][j] = oo;
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
        int ans = 0;
        for(auto &i : nm){
            for(auto &j : nm) ans = max(ans, d[i][j]);
        }
        cout << "Network " << (cn+1) << ": ";
        if(ans == oo) cout << "DISCONNECTED\n";
        else cout << ans << "\n";
        cout << "\n";
        cn++;
    }
    
    return 0;
}
