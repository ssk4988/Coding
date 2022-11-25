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
    //case where they are same
    int n;
    cin >> n;
    while(n > 0){
        ll dp[1001];
        bool visited[1001];
        memset(visited, false, sizeof visited);
        memset(dp, -1, sizeof dp);
        vector<pair<pi, int>> tzs(n);
        vector<vector<pi>> edges(1001);
        rep(i, 0, n){
            int a, b, c; cin >> a >> b >> c;
            tzs[i] = {{a, b}, c};
            edges[a].pb({b, c});
            edges[b].pb({a, c});
        }
        int start, end; cin >> start >> end;
        dp[start] = 0;
        priority_queue<pair<ll, int>> q;
        q.push({dp[start], start});
        while(!q.empty()){
            pair<ll, int> p = q.top(); q.pop();
            if(visited[p.s]) continue;;
            visited[p.s] = true;
            for(pi &e : edges[p.s]){
                if(!visited[e.f] && dp[e.f] == -1 || dp[e.f] > dp[p.s] + (p.s + e.f) * (ll)e.s){
                    dp[e.f] = dp[p.s] + (p.s + e.f) * (ll)e.s;
                    q.push({-dp[e.f], e.f});
                }
            }
        }
        cout << fixed << setprecision(3) << (ld)dp[end] / 100 << nL;

        cin >> n;
    }
    
    return 0;
}