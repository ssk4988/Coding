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
        int n, m; cin >> n >> m;
        vl c(n);
        rep(i, 0, n){
            cin >> c[i];
        }
        vvi attr(n, vi(m));
        vvi lower(n, vi(m, -1)), higher(n, vi(m, -1));
        vector<vpi> order(m);
        rep(i, 0, n){
            rep(j, 0, m){
                cin >> attr[i][j];
                order[j].pb({attr[i][j], i});
            }
        }
        rep(i, 0, m){
            sort(all(order[i]));
            for(int j = 1; j < n; j++){
                lower[order[i][j].s][i] = order[i][j-1].s;
            }
            for(int j = n - 2; j >= 0; j--){
                higher[order[i][j].s][i] = order[i][j+1].s;
            }
        }
        using state = tuple<int, int, int>; // idx, attribute, bought;
        using p = pair<ll, state>;
        priority_queue<p, vector<p>, greater<p>> pq;
        vl dist(n * m * 2, 1e15);
        auto adj = [&](state s) -> vector<p> {
            auto [idx, att, bought] = s;
            vector<p> a;
            if(bought){
                if(att > 0){
                    a.push_back({0, {idx, att-1, bought}});
                }
                if(att + 1 < m){
                    a.push_back({0, {idx, att+1, bought}});
                }
            }
            else{
                a.push_back({c[idx], {idx, att, 1}});
            }
            if(lower[idx][att] != -1){
                a.push_back({abs(attr[lower[idx][att]][att] - attr[idx][att]), {lower[idx][att], att, 0}});
            }
            if(higher[idx][att] != -1){
                a.push_back({0, {higher[idx][att], att, 0}});
            }
            a.push_back({0, {idx, att, 0}});
            return a;
        };
        auto to_idx = [&](state s) -> int {
            auto [idx, att, bought] = s;
            return idx * m * 2 + att * 2 + bought;
        };
        rep(i, 0, m){
            state s = {0, i, 1};
            dist[to_idx(s)] = 0;
            pq.push({0, s});
        }
        ll ans = -1;
        while(!pq.empty()){
            auto [d, s] = pq.top(); pq.pop();
            if(dist[to_idx(s)] < d) continue;
            auto [idx, att, bought] = s;
            // cout << "visited " << " pkmn " << idx << " att " << att << " bought:" << bought << " switched: " << switched << " left: " << left << " expander: " << expander << " dist: " << d << "\n";
            if(idx == n-1 && bought){
                ans = d;
                break;
            }
            auto a = adj(s);
            for(auto [w, nxt] : a){
                if(dist[to_idx(nxt)] > w + d){
                    dist[to_idx(nxt)] = w + d;
                    pq.push({w + d, nxt});
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
