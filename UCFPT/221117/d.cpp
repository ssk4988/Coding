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

struct cell {
    int r;
    int c;
    vector<pi> ns;
    bool visited = false;
    int dist = 10000;
    cell(int x1, int y1){
        r = x1;
        c = y1;
    }
};


vi startrows;
vector<vector<cell>> cs;

pi getindices(int k){
    int i;
    for(i = 0; i < startrows.size(); i++){
        if(startrows[i] > k){
            break;
        }
    }
    i--;
    return {i, k - startrows[i]};
}
bool isvalid(int i, int j){
    if(i < 0 || i >= cs.size()) return false;
    if(j < 0 || j >= cs[i].size()) return false;
    return true;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, n, a, b, x; cin >> r >> n >> a >> b >> x;
    a--; b--; 
    int cur = 0;
    rep(i, 0, r - 1){
        startrows.pb(cur);
        cs.pb({});
        rep(j, 0, r + i){
            cs[cs.size() - 1].pb(cell(cs.size() - 1, j));
        }
        cur += r + i;
    }
    for(int i = r - 1; i >= 0; i--){
        startrows.pb(cur);
        cs.pb({});
        rep(j, 0, r + i){
            cs[cs.size() - 1].pb(cell(cs.size() - 1, j));
        }
        cur += r + i;
    }
    rep(i, 0, x){
        int k; cin >> k;
        pi k1 = getindices(k - 1);
        cs[k1.f][k1.s].visited = true;
    }
    for(auto &v : cs){
        for(auto &c : v){
            if(isvalid(c.r, c.c - 1)) 
                c.ns.pb({c.r, c.c - 1});
            if(isvalid(c.r, c.c + 1)) c.ns.pb({c.r, c.c + 1});
            if(isvalid(c.r + 1, c.c)) c.ns.pb({c.r+1, c.c });
            if(isvalid(c.r - 1, c.c)) c.ns.pb({c.r-1, c.c});
            if(c.r < r && isvalid(c.r - 1, c.c - 1)) c.ns.pb({c.r-1, c.c - 1});
            if(c.r + 1 < r && isvalid(c.r + 1, c.c + 1)) c.ns.pb({c.r+1, c.c + 1});
            if(c.r >= r && isvalid(c.r - 1, c.c + 1)) c.ns.pb({c.r-1, c.c + 1});
            if(c.r + 1 >= r && isvalid(c.r + 1, c.c - 1)) c.ns.pb({c.r+1, c.c - 1});
            c.dist = 9999;
        }
    }
    pi aind = getindices(a);
    pi bind = getindices(b);
    cell *ac = &cs[aind.f][aind.s];
    cell *bc = &cs[bind.f][bind.s];
    ac->dist = 0;
    queue<cell*> q;
    q.emplace(ac);
    while(!q.empty()){
        cell *k = q.front();
        q.pop();
        if(k->visited) continue;
        k->visited = true;
        for(pi p : k->ns){
            cell *k1 = &cs[p.f][p.s];
            if(k1->dist > k->dist + 1 && !k1->visited){
                k1->dist = k->dist + 1;
                q.emplace(k1);
            }
        }
    }
    if(bc->dist <= n){
        cout << bc->dist << nL;
    }
    else{
        cout << "No" << nL;
    }
    
    return 0;
}