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
    vi arr(n), numc(n), ans(n);
    rep(i, 0, n) cin >> arr[i];
    vvi adj(n);
    rep(i, 0, n- 1){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<unordered_set<int>*> mm(n);
    auto dfs = [&](int cur, int pre, int path, auto &&dfs)->void{
        for(int i : adj[cur]){
            if(i==pre) continue;
            numc[cur]++;
            dfs(i, cur, path ^ arr[i], dfs);
            ans[cur] += ans[i];
        }
        mm[cur] = new unordered_set<int>();
        if(numc[cur] == 0){
            mm[cur]->insert(path);
            // ans[cur] = 0;
        }
        else{
            for(int i : adj[cur]){
                if(i==pre) continue;
                if(sz(*mm[i]) > sz(*mm[cur])) mm[cur] = mm[i];
            }
            bool dup = false;
            unordered_set<int> ss;
            for(int i : adj[cur]){
                if(i==pre) continue;
                if(mm[i] == mm[cur]) continue;
                for(int j : *mm[i]){
                    if(mm[cur]->count(j) || ss.count(j)) dup = true;
                    ss.insert(j);
                    // mm[cur]->insert(j);
                }
            }
            int maxf = 1;
            if(dup){
                unordered_map<int, int> freq;
                for(int i : adj[cur]){
                    if(i==pre) continue;
                    for(int j : *mm[i]){
                        freq[j]++;
                        if(freq[j] > maxf) maxf = freq[j];
                    }
                }
                // cout << "has a dup in " << (cur + 1) << nL;
                mm[cur]->clear();
                for(auto &p : freq){
                    if(p.s == maxf) mm[cur]->insert(p.f);
                }
            }
            else{
                for(int i : adj[cur]){
                    if(i==pre) continue;
                    if(mm[i] == mm[cur]) continue;
                    for(int j : *mm[i]){
                        // if(mm[cur]->count(j)) dup = true;
                        mm[cur]->insert(j);
                    }
                }
            }
            ans[cur] += numc[cur] - maxf;
        }
        // cout << (cur + 1) << ": ";
        // for(int i : *mm[cur]) cout << i << " ";
        // cout << " ans: " << ans[cur];
        // cout << nL;
    };
    dfs(0, -1, arr[0], dfs);
    unordered_set<int> res = *mm[0];
    cout << (ans[0] + (1 - res.count(0))) << nL;
    
    return 0;
}
