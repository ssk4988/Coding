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

int inf = 1e8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        map<int, int> freq;
        int n, m; cin >> n >> m;
        vvi adj(n);
        rep(i, 0, m){
            int a, b; cin >> a>>b; a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        rep(i, 0, n){
            freq[sz(adj[i])]++;
        }
        int kflowertype = sqrt(n);
        // k flower has k^2 nodes
        if(kflowertype * kflowertype != n || freq[4] != kflowertype || freq[2] != (n - kflowertype) || kflowertype == 1 || kflowertype == 2){
            cout << "NO\n";
            continue;
        }
        vi visited(n);
        bool works = true;
        auto dfs2 = [&](int cur, auto &&dfs2)->int{
            int cnt = 1;
            visited[cur] = true;
            int times = 0;
            int n4 = 0;
            for(int i : adj[cur]){
                if(sz(adj[i]) == 4) n4++;
                if(visited[i] || sz(adj[i]) != 2) continue;
                cnt += dfs2(i, dfs2);
                times++;
            }
            if(times != 1 && n4 != 1) 
                return -inf;
            return cnt;
        };
        auto n4cycle = [&](int cur, int pre, auto &&n4cycle)->int{
            visited[cur] = true;
            int ans = 1;
            int nadj = 0;
            int nadjv = 0;
            for(int i : adj[cur]){
                if(sz(adj[i]) != 4) continue;
                nadj++;
                if(i == pre) continue;
                if(visited[i]) continue;
                nadjv++;
                ans += n4cycle(i, cur, n4cycle);
            }
            // visited[cur] = false;
            if(nadj != 2) return -inf;
            return ans;
        };
        rep(i, 0, n){
            if(sz(adj[i]) == 4){
                int n4c = n4cycle(i, -1, n4cycle);
                // cout << "num 4 cycle: " << n4c << " k-flower: " << kflowertype<< nL;
                if(n4c != kflowertype){
                    works = false;
                }
                // iota(all(visited), 0);
                rep(j, 0, n) visited[j] = false;
                break;
            }
        }
        int cnt4 = 0;
        rep(i, 0, n){
            if(sz(adj[i]) == 4){
                cnt4++;
                if(visited[i]){
                    works = false;
                    break;
                }
                int res = dfs2(i, dfs2);
                if(res != kflowertype){
                    works = false;
                    break;
                }
                int n4 = 0;
                for(int j : adj[i]){
                    if(sz(adj[j])==4){
                        n4++;
                    }
                }
                if(n4 != 2){
                    works = false;
                    break;
                }
            }
        }
        cout << (works ? "YES": "NO") << nL;
    }
    
    return 0;
}
