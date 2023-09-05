#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; cin >> n;
        vi lens(n);
        map<pi, int> dist;
        rep(i, 0, n){
            cin >> lens[i];
            lens[i]++;
            rep(j, 0, lens[i]){
                dist[{i, j}] = INT_MAX;
            }
        }

        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        r1--, r2--;
        dist[{r1, c1}] = 0;
        priority_queue<pair<int, pi>, vector<pair<int, pi>>, greater<pair<int, pi>>> pq;
        pq.push({0, {r1, c1}});
        set<pi> vs;
        while(!pq.empty()){
            auto [d, p] = pq.top(); pq.pop();
            if(vs.count(p)) continue;
            vs.insert(p);
            auto [r, c] = p;
            if(r){
                pi nex = {r - 1, min(c, lens[r-1] - 1)};
                if(!vs.count(nex) && dist[nex] > d + 1){
                    dist[nex] = d + 1;
                    pq.push({dist[nex], nex});
                }
            }
            if(r + 1 < n){
                pi nex = {r + 1, min(c, lens[r+1] - 1)};
                if(!vs.count(nex) && dist[nex] > d + 1){
                    dist[nex] = d + 1;
                    pq.push({dist[nex], nex});
                }
            }
            if(r || c){
                pi nex = c ? pi{r, c-1} : pi{r-1, lens[r-1]-1};
                if(!vs.count(nex) && dist[nex] > d + 1){
                    dist[nex] = d + 1;
                    pq.push({dist[nex], nex});
                }
            }
            if(!(r == n - 1 && lens[r] == c + 1)){
                pi nex = lens[r] == c + 1 ? pi{r + 1, 0} : pi{r, c + 1};
                if(!vs.count(nex) && dist[nex] > d + 1){
                    dist[nex] = d + 1;
                    pq.push({dist[nex], nex});
                }
            }
        }
        cout << dist[{r2, c2}] << "\n";
    }
}
