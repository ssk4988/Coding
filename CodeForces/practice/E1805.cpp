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

struct mad{
    unordered_map<int, int> freq;
    set<int> ss;
    void add(int i){
        freq[i]++;
        if(freq[i] == 2){
            ss.insert(i);
        }
    }
    void rem(int i){
        freq[i]--;
        if(freq[i] == 1){
            ss.erase(i);
        }
    }
    int getmad(){
        if(ss.size()) return *ss.rbegin();
        return 0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    map<pi, int> eid;
    vi ans(n - 1);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
        eid[{a, b}] = i;
        eid[{b, a}] = eid[{a, b}];
    }
    vi a(n);
    mad whole;
    rep(i, 0, n) {
        cin >> a[i];
        whole.add(a[i]);
    }
    if(whole.freq[whole.getmad()] > 2){
        // rep(i, 0, n - 1) ans[i] = whole.getmad();
        ans = vi(n - 1, whole.getmad());
    }
    else{
        int mad2 = 0;
        for(pi p : whole.freq){
            if(p.s == 2) mad2 = max(mad2, p.f);
        }
        if(mad2 != 0){
            ans = vi(n - 1, -1);
            vi locs;
            rep(i, 0, n){
                if(a[i] == mad2) locs.pb(i);
            }
            vi ondiam(n);
            auto findtarget = [&](int cur, int pre, int target, auto &&findtarget)->bool{
                for(int i : adj[cur]){
                    if(i == pre) continue;
                    if(findtarget(i, cur, target, findtarget)) {ondiam[cur] = true; return true;}
                }
                return cur == target;
            };
            ondiam[locs[0]] = ondiam[locs[1]] = true;
            int nei = -1;
            for(int i : adj[locs[0]]){
                if(findtarget(i, locs[0], locs[1], findtarget)){
                    nei = i;break;
                }
            }
            mad m1, m2;
            auto add = [&](mad &m, int cur, int pre, auto &&add)->void{
                m.add(a[cur]);
                for(int i : adj[cur]){
                    if(i == pre) continue;
                    add(m, i, cur, add);
                }
            };
            auto dfs = [&](int cur, int pre, int target, mad &m, auto &&dfs)->void{
                if(ondiam[cur]) ans[eid[{pre, cur}]] = max(ans[eid[{pre, cur}]], m.getmad());
                if(cur == target) return;
                m.add(a[cur]);
                for(int i : adj[cur]){
                    if(i == pre) continue;
                    dfs(i, cur, target, m, dfs);
                }
                m.rem(a[cur]);
            };
            m1.add(a[locs[0]]);
            for(int i : adj[locs[0]]){
                if(nei != i){
                    add(m1, i, locs[0], add);
                }
            }
            dfs(nei, locs[0], locs[1], m1, dfs);
            m2.add(a[locs[1]]);
            for(int i : adj[locs[1]]){
                if(findtarget(i, locs[1], locs[0], findtarget)){
                    nei = i; break;
                }
            }
            for(int i : adj[locs[1]]){
                if(nei != i){
                    add(m2, i, locs[1], add);
                }
            }
            dfs(nei, locs[1], locs[0], m2, dfs);
            rep(i, 0, n - 1){
                if(ans[i] == -1) ans[i] = mad2;
            }
        }
    }
    rep(i, 0, n - 1){
        cout << ans[i] << nL;
    }

    
    return 0;
}
