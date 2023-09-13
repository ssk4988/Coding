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
        int n; cin >> n;
        vi nex(n);
        vl c(n);
        vi inc(n);
        rep(i, 0, n){
            cin >> nex[i]; nex[i]--;
            inc[nex[i]]++;
        }
        rep(i, 0, n) cin >> c[i];
        vi visited(n);
        ll sub = 0;
        vi rem(n);
        vi rems;
        
        auto dfs = [&](int cur, auto && dfs)->void{
            if(visited[cur] == 2) return;
            if(visited[cur] == 1){
                int v = nex[cur];
                pl mn = {c[cur], cur};
                while(v != cur){
                    mn = min(mn, {c[v], v});
                    v = nex[v];
                }
                sub += mn.f;
                rem[mn.s] = true;
                rems.pb(mn.s);
                // inc[nex[mn.s]]--;
                return;
            }
            visited[cur] = 1;
            dfs(nex[cur], dfs);
            visited[cur] = 2;
        };
        ll sum = 0;
        rep(i, 0, n){
            sum += c[i];
            if(visited[i]) continue;
            dfs(i, dfs);
        }
        ll ans = 2 * sum - sub;
        // cout << "for case " << (cn + 1) << ": " << ans << nL;
        queue<int> q;
        // auto dd = [&](int cur, auto &&dd)->void{
        //     if(rem[cur]) return;
        //     cout << (cur+1) << " ";
        //     rem[cur] = true;
        //     dd(nex[cur], dd);
        // };
        
        rep(i, 0, n){
            if(inc[i] == 0){
                // dd(i, dd);
                q.push(i);
            }
        }
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(rem[cur]) continue;
            rem[cur] = true;
            cout << (cur + 1) << " ";
            inc[nex[cur]]--;
            if(inc[nex[cur]] == 0 && !rem[nex[cur]]){
                q.push(nex[cur]);
            }
        }
        for(int i : rems){
            inc[nex[i]]--;
        }
        rep(i, 0, n){
            if(!rem[i] && inc[i] == 0){
                // dd(i, dd);
                q.push(i);
            }
        }
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(rem[cur]) continue;
            rem[cur] = true;
            cout << (cur + 1) << " ";
            inc[nex[cur]]--;
            if(inc[nex[cur]] == 0 && !rem[nex[cur]]){
                q.push(nex[cur]);
            }
        }
        for(int i : rems) cout << (i + 1) << " ";
        cout << nL;
    }
    
    return 0;
}