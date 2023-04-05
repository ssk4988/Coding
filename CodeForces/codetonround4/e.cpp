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
        int n, m;
        cin >> n >> m;
        vi a(n);
        vvi adj(n);
        vi startpoint(n, false);
        rep(i, 0, n){
            cin >> a[i];
            if(a[i] == 0) startpoint[i] = true;
        }
        rep(i, 0, m){
            int e1, e2; cin >> e1 >> e2;
            e1--;e2--;
            adj[e1].pb(e2);
            adj[e2].pb(e1);
        }
        bool winnable = false;
        vi qd(n); // queued
        vi pd(n); //processed
        vi qdud, pdud;
        rep(i, 0, n){
            if(!startpoint[i]) continue;
            priority_queue<pi, vpi, greater<pi>> pq;
            queue<int> q;
            int numpd = 0;
            qd[i] = true;
            qdud.pb(i);
            q.push(i);
            while(!q.empty()){
                int v= q.front(); q.pop();
                if(pd[v]) continue;;
                startpoint[v] = false;
                pd[v] = true;
                pdud.pb(v);
                numpd++;
                for(int j : adj[v]){
                    if(!qd[j]){
                        pq.push({a[j], j});
                        qd[j] = true;
                        qdud.pb(j);
                    } 
                }
                while(pq.size() && pq.top().f <= numpd){
                    pi p = pq.top();pq.pop();
                    q.push(p.s);
                }
            }
            for(int j : qdud){
                qd[j] = false;
            }
            for(int j : pdud){
                pd[j] = false;
            }
            qdud.clear(); pdud.clear();
            if(numpd == n){
                winnable = true;
                break;
            }
        }
        cout << (winnable ? "YES": "NO") << nL;
    }
    
    return 0;
}
