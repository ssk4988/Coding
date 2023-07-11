#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vpi ans;
        auto printout = [&]()->void{
            cout << "Case " << (cn + 1) << ": " << sz(ans) << "\n";
            for(pi &p : ans){
                cout << p.first << " " << p.second << "\n";
            }
            cout << "\n";
        };
        vvi adj(n);
        vi degfreq(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        rep(i, 0, n){
            degfreq[sz(adj[i])]++;
        }
        vi comp(n, -1);
        auto dfs = [&](int cur, int p, int c, auto &&dfs)->void{
            comp[cur] = c;
            for(int i : adj[cur]){
                if(p == i || comp[i] != -1) continue;
                dfs(i, cur, c, dfs);
            }
        };
        auto line = [&](int start, int p)->pi{
            // make start be adj of p in direction of potential line
            int cur = start, par = p;
            int cnt = 1;
            while(sz(adj[cur]) > 1 && cur != p && !(cur == start && cnt > 1)){
                if(sz(adj[cur]) != 2) return {false, -1};
                for(int i : adj[cur]){
                    if(i == par) continue;
                    cnt++;
                    par = cur;
                    cur = i;
                    break;
                }
            }
            if(cur == start && cnt > 1) return {false, -1};
            if(cur == p) return {false, -1};
            return {true, cnt};
        };
        auto cycle = [&](int start, int p)->pi{
            // make start adj of p, where p is hub
            int cur = start, par = p;
            int cnt = 1;
            while(cur != p){
                if(sz(adj[cur]) != 2) return {false, -1};
                for(int i : adj[cur]){
                    if(i == par) continue;
                    cnt++;
                    par = cur;
                    cur = i;
                    break;
                }
            }
            return {true, cnt};
        };
        auto dist2 = [&](int start, int p, int target)->int{
            // start is adj to p which is hub, target is other hub
            int cnt = 1;
            int cur =start, par = p;
            while(cur != target){
                if(sz(adj[cur]) != 2) return -1;
                for(int i : adj[cur]){
                    if(i == par) continue;
                    cnt++;
                    par = cur;
                    cur = i;
                    break;
                }
            }
            return cnt;
        };
        int cc = 0;
        rep(i, 0, n){
            if(comp[i] == -1){
                dfs(i, -1, cc, dfs);
                cc++;
            }
        }
        if(cc != 1){
            printout();
            continue;
        }
        if(degfreq[2] == n){
            // is only cycle
            if(n >= 6 && (n - 6) % 6 == 0){
                ans.pb({0, (n - 6) / 6}); // is 0
            }
        }
        if(degfreq[2] == n - 2 && degfreq[1] == 2){
            if(n >= 3 && (n - 3) % 2 == 0){
                ans.pb({1, (n - 3) / 2}); // is 1
            }
            if(n >= 6 && (n - 6) % 5 == 0){
                ans.pb({2, (n - 6) / 5}); // is 2
                ans.pb({5, (n - 6) / 5}); // is 5
            }
            if(n >= 4 && (n - 4) % 3 == 0){
                ans.pb({7, (n - 4) / 3}); // is 7
            }
        }
        if(degfreq[3] == 1 && degfreq[1] == 3 && degfreq[2] == n - 3 - 1){
            //3,4
            int hub3 = -1;
            rep(i, 0, n){
                if(sz(adj[i]) == 3){
                    hub3 = i;
                }
            }
            bool works = true;
            vi degs;
            for(int i : adj[hub3]){
                // cout << "line from " << hub3 << " to " << i << "\n";
                pi res = line(i, hub3);
                if(res.first != true){
                    works = false;
                    break;
                }
                degs.pb(res.second);
            }
            if(works){
                sort(all(degs));
                assert(sz(degs) == 3);
                if(degs[0] * 2 == degs[1] && degs[0] * 2 == degs[2]){
                    ans.pb({3, degs[0] - 1});
                }
                if(degs[0] == degs[1] && degs[0] * 2 == degs[2]){
                    ans.pb({4, degs[0] - 1});
                }
            }
        }
        if(degfreq[3] == 1 && degfreq[1] == 1 && degfreq[2] == n - 1 - 1){
            //6,9
            // cout << "testing 69" << "\n"; // nice
            vi cycles;
            vi lines;
            int hub3 = -1;
            rep(i, 0, n){
                if(sz(adj[i]) == 3){
                    hub3 = i;
                }
            }
            for(int i : adj[hub3]){
                pi res = line(i, hub3);
                if(res.first){
                    lines.pb(res.second);
                    // cout << "line of" << res.second << "\n";
                }
                res = cycle(i, hub3);
                if(res.first){
                    cycles.pb(res.second);
                    // cout << "cycle of " << res.second << "\n";
                }
            }
            if(sz(lines) == 1 && sz(cycles) == 2 && cycles[0] == cycles[1] && lines[0] >= 2 && (lines[0] - 2) % 2 == 0 && cycles[0] >= 4 && (cycles[0] - 4) % 4 == 0){
                int k1 = (lines[0] - 2) / 2;
                int k2 = (cycles[0] - 4) / 4;
                if(k1 == k2){
                    ans.pb({6, k1});
                    ans.pb({9, k1});
                }
            }
        }
        if(degfreq[3] == 2 && degfreq[2] == n - 2){
            vi hub3;
            rep(i, 0, n){
                if(sz(adj[i]) == 3){
                    hub3.pb(i);
                }
            }
            vi v1;
            for(int i : adj[hub3[0]]){
                int v = dist2(i, hub3[0], hub3[1]);
                v1.pb(v);
            }
            sort(all(v1));
            if(v1[0] != -1 && v1[0] * 3 == v1[1] && v1[0] * 3 == v1[2]){
                int k = v1[0] - 1;
                ans.pb({8, k});
            }
        }
        sort(all(ans));
        printout();
    }
}