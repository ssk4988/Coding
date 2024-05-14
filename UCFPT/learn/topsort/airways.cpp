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

const int MAX_N = 100005;
vi ed[MAX_N];
int indeg[MAX_N];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int m; cin >> m;
        map<string, int> rl;
        vvi in, out;
        vi fs;
        rep(i, 0, m){
            string a, b; int id; cin >> a >> b >> id;
            fs.pb(id);
            if(!rl.count(a)) rl[a] = sz(rl);
            if(!rl.count(b)) rl[b] = sz(rl);
            while(sz(in) < sz(rl)){
                in.pb({}), out.pb({});
            }
            in[rl[b]].pb(id);
            out[rl[a]].pb(id);
        }
        rep(i, 0, sz(in)){
            for(int a : in[i]){
                for(int b : out[i]){
                    ed[a].pb(b);
                    indeg[b]++;
                }
            }
        }
        priority_queue<int, vi, greater<int>> pq;
        for(int i : fs){
            if(indeg[i] == 0){
                pq.push(i);
            }
        }
        while(!pq.empty()){
            int u = pq.top(); pq.pop();
            cout << u << " ";
            for(int v : ed[u]){
                indeg[v]--;
                if(indeg[v] == 0){
                    pq.push(v);
                }
            }
        }
        for(int u : fs){
            indeg[u] = 0;
            ed[u].clear();
        }
        cout << "\n";
    }
    
    return 0;
}
