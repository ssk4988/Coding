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
    int n, f, m; cin >> n >> f >> m;
    vi term(n);
    vvi lower(n, vi(26, -1)), upper(n, vi(26, -1));
    rep(i, 0, f){
        int v; cin >> v; v--;
        term[v] = true;
    }
    rep(i, 0, m){
        int s1, s2;
        char c; cin >> s1 >> c >> s2;
        s1--, s2--;
        if(islower(c)){
            lower[s1][c - 'a'] = s2;
        }
        else{
            upper[s1][c - 'A'] = s2;
        }
    }
    using state = tuple<int, int, bool, bool, bool>;
    map<state, int> dist;
    priority_queue<pair<int, state>, vector<pair<int, state>>, greater<pair<int, state>>> pq;
    dist[{0, 0, 0, 1, 1}] = 0;
    pq.push({0, {0, 0, 0, 1, 1}});
    int ans = -1;
    auto add = [&](state s, int d) -> void {
        if(!dist.count(s) || d < dist[s]){
            dist[s] = d;
            pq.push({d, s});
        }
    };
    while(!pq.empty()){
        auto [d, s] = pq.top(); pq.pop();
        auto [s1, s2, diff, m1, m2] = s;
        if(d > dist[s]) continue;
        if(diff && term[s1] && term[s2]){
            ans = d;
            break;
        }
        if(m1){
            add({s1, s2, diff, 0, m2}, d);
        }
        if(m2){
            add({s1, s2, diff, m1, 0}, d);
        }
        // upper
        rep(i, 0, 26){
            if(upper[s1][i] == -1 || upper[s2][i] == -1) continue;
            add({upper[s1][i], upper[s2][i], diff, 1, 1}, d + 2);
        }
        vi s1lower, s2lower;
        rep(i, 0, 26){
            if(lower[s1][i] != -1) s1lower.pb(i);
            if(lower[s2][i] != -1) s2lower.pb(i);
        }
        if(m1 && m2){
            for(int i : s1lower){
                for(int j : s2lower){
                    add({lower[s1][i], lower[s2][j], diff || i != j, m1, m2}, d + 2);
                }
            }
        }
        else if(m1 && !m2){
            for(int i : s1lower){
                add({lower[s1][i], s2, diff || true, m1, m2}, d + 1);
            }
        }
        else if(!m1 && m2){
            for(int i : s2lower){
                add({s1, lower[s2][i], diff || true, m1, m2}, d + 1);
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
