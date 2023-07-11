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
        int n, m; cin >> n >> m;
        vvi adj(n);
        vi c(n), s(n), f(n);
        rep(i, 0, n){
            cin >> c[i]; c[i]--;
        }
        rep(i, 0, n){
            cin >> s[i]; s[i]--;
        }
        rep(i, 0, n){
            cin >> f[i]; f[i]--;
        }
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi ss;
        auto canvisit = [&](vi &keys, bool rev)->vi{
            vi havekey(n);
            // havekey[keys[0]] = true;
            vvi qs(n);
            queue<int> q;
            q.push(0);
            vi visited(n);
            // q[keys[0]].p
            while(!q.empty()){
                int k = q.front(); q.pop();
                if(visited[k] || (rev && !ss[k])) continue;
                havekey[keys[k]] = true;
                visited[k] =true;
                for(int i : qs[keys[k]]){
                    q.push(i);
                }
                qs[keys[k]].clear();
                for(int i : adj[k]){
                    if(visited[i]) continue;
                    if(havekey[c[i]] || (c[i] == keys[i] && rev)) q.push(i);
                    else qs[c[i]].pb(i);
                }
            }
            // rep(i, 0, n) if(!visited[i] && !(!rev && s[i] == f[i])) return false;
            return visited;
        };

        ss = canvisit(s, false);
        vi ff = canvisit(f, true);
        bool works = true;
        rep(i, 0, n){
            if(!ss[i] && s[i] != f[i]) works = false;
            // if(f[0] != c[0] && (i > 0 && s[i] != f[i])) works = false;
        }
        if(works) cout << "YES\n";
        else cout << "NO\n";

    }

    
    return 0;
}