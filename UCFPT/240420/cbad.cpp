#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vi votes(m);
    vvi pref(m, vi(n));
    rep(i, 0, m){
        cin >> votes[i];
        string str; cin >> str;
        rep(j, 0, n){
            pref[i][str[j] - 'A'] = j;
        }
    }
    vi adj(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == j) continue;
            int sc = 0;
            rep(k, 0, m){
                if(pref[k][i] < pref[k][j]) sc += votes[k];
                else sc -= votes[k];
            }
            if(sc > 0) adj[i] |= 1 << j;
        }
    }
    rep(i, 0, n){
        cout << i << ": ";
        rep(j, 0, n){
            if((adj[i] >> j) & 1) cout << j << " ";
        }
        cout << "\n";
    }
    int target = (1 << n) - 1;
    rep(i, 0, n){
        int seen = 0;
        int cur = i;
        int use = 0;
        while(seen != target){
            int best = -1, bestcnt = -1;
            use |= 1 << cur; 
            seen |= adj[cur];
            rep(nex, 0, n){
                if(!((adj[cur] >> nex) & 1)) continue;
                if(use & (1 << nex)) continue;
                int cont = __builtin_popcount((~seen) & adj[nex]);
                if(cont > bestcnt){
                    bestcnt = cont;
                    best = nex;
                }
            }
            if(best == -1) break;
            cur = best;
        }
        cout << char('A' + i) << ": " << (seen == target ? "can win" : "can't win") << "\n";
    }
    // vvi dp(1 << n, vi(n, -1));
    // auto go = [&](int mask, int pre, auto &&go)-> int {
    //     int &ans = dp[mask][pre];
    //     if(ans != -1) return ans;
    //     if(mask == (1 << n) - 1) return ans = 1;
    //     ans = 0;
    //     rep(i, 0, n){
    //         if(((adj[pre] >> i) & 1) && !((mask >> i) & 1)) ans = max(ans, go(mask | (1 << i), i, go));
    //     }
    //     return ans;
    // };
    // rep(i, 0, n){
    //     int res = go(1 << i, i, go);
    //     cout << char('A' + i) << ": " << (res == 1 ? "can win" : "can't win") << "\n";
    // }

    return 0;
}