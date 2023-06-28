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
    int n, m; cin >> n >> m;
    vector<vl> adj(n, vl(n, -1));
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        ll c; cin >> c;
        adj[a][b] = c;
        adj[b][a] = c;
    }
    vi cut(n);
    cut[0] = true;
    ll score = 0;
    vvi games;
    vl scores;
    // case out inf?
    bool canbeinf = false;
    while(true){
        if(cut[n - 1]) break;
        ll minedge = LLONG_MAX;
        int edgesfound = 0;
        rep(i, 0, n){
            if(!cut[i]) continue;
            rep(j, 0, n){
                if(cut[j] || adj[i][j] == -1) continue;
                edgesfound++;
                minedge = min(minedge, adj[i][j]);
            }
        }
        if(edgesfound == 0){
            canbeinf = true;
            break;
        }
        scores.pb(minedge);
        score += minedge;
        games.pb(vi(n));
        rep(i, 0, n){
            if(cut[i]){
                games.back()[i] = 1;
            }
        }
        vi newcut;
        rep(i, 0, n){
            if(!cut[i]) continue;
            rep(j, 0, n){
                if(cut[j] || adj[i][j] == -1) continue;
                adj[i][j] -= minedge;
                adj[j][i] -= minedge;
                assert(adj[i][j] >= 0);
                if(adj[i][j] == 0){
                    newcut.pb(j);
                }
            }
        }
        for(int i : newcut) cut[i] = true;
    }
    if(canbeinf){
        cout << "inf\n";
    }
    else{
        cout << score << " " << sz(games) << nL;
        rep(i, 0, sz(games)){
            rep(j, 0, n){
                cout << games[i][j];
            }
            cout << " " << scores[i];
            cout << nL;
        }
    }
    
    
    return 0;
}
