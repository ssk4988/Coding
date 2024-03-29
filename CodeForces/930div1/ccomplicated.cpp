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
        vector<map<int, vi>> expands(m);
        rep(i, 0, n){
            rep(j, 0, m){
                cin >> attr[i][j];
                order[j].pb({attr[i][j], i});
                expands[j][attr[i][j]].push_back(i);
            }
        }
        rep(i, 0, m){
            sort(all(order[i]));
            int nxt = -1;
            for(int j = 1; j < n; j++){
                if(order[i][j].f > order[i][j-1].f){
                    nxt = order[i][j-1].s;
                }
                lower[order[i][j].s][i] = nxt;
            }
            nxt = -1;
            for(int j = n - 2; j >= 0; j--){
                if(order[i][j].f < order[i][j+1].f){
                    nxt = order[i][j+1].s;
                }
                higher[order[i][j].s][i] = nxt;
            }
            // rep(j, 0, n-1){
            //     next[order[i][j].s][i] = order[i][j+1].s;
            // }
        }
        using state = tuple<int, int, int, int, int, int>; // idx, attribute, bought, switched, left/right, expander;
        using p = pair<ll, state>;
        priority_queue<p, vector<p>, greater<p>> pq;
        map<state, ll> dist;
        auto adj = [&](state s) -> vector<p> {
            auto [idx, att, bought, switched, left, expander] = s;
            vector<p> a;
            if(expander){
                for(int idx1 : expands[att][attr[idx][att]]){
                    a.push_back({0, {idx1, att, 0, 0, 0, 0}});
                }
                return a;
            }
            if(bought){
                if((!switched || left) && att > 0){
                    a.push_back({0, {idx, att-1, bought, 1, 1, 0}});
                }
                if((!switched || !left) && att + 1 < m){
                    a.push_back({0, {idx, att+1, bought, 1, 0, 0}});
                }
            }
            else{
                a.push_back({c[idx], {idx, att, 1, 0, 0, 0}});
            }
            if(lower[idx][att] != -1){
                a.push_back({abs(attr[lower[idx][att]][att] - attr[idx][att]), {lower[idx][att], att, 0, 0, 0, 1}});
            }
            if(higher[idx][att] != -1){
                a.push_back({0, {higher[idx][att], att, 0, 0, 0, 1}});
            }
            a.push_back({0, {idx, att, 0, 0, 0, 1}});
            return a;
        };
        rep(i, 0, m){
            state s = {0, i, 1, 0, 0, 0};
            dist[s] = 0;
            pq.push({0, s});
        }
        ll ans = -1;
        while(!pq.empty()){
            auto [d, s] = pq.top(); pq.pop();
            if(dist[s] < d) continue;
            auto [idx, att, bought, switched, left, expander] = s;
            // cout << "visited " << " pkmn " << idx << " att " << att << " bought:" << bought << " switched: " << switched << " left: " << left << " expander: " << expander << " dist: " << d << "\n";
            if(idx == n-1 && bought){
                ans = d;
                break;
            }
            auto a = adj(s);
            for(auto [w, nxt] : a){
                if(!dist.count(nxt)){
                    dist[nxt] = 1e15;
                }
                if(dist[nxt] > w + d){
                    dist[nxt] = w + d;
                    pq.push({w + d, nxt});
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
