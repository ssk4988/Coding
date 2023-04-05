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

vi arr;

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (arr[b] == 0 && arr[a] != 0) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m;
        cin >> n >> m;
        arr.clear();
        arr.resize(n);
        vvi adj(n);
        // vi startpoint(n, false);
        rep(i, 0, n){
            cin >> arr[i];
            // if(arr[i] == 0) startpoint[i] = true;
        }
        rep(i, 0, m){
            int e1, e2; cin >> e1 >> e2;
            e1--;e2--;
            adj[e1].pb(e2);
            adj[e2].pb(e1);
        }
        UF uf(n);
        bool winnable = false;
        vi qd(n); // queued
        vi pd(n); //processed
        priority_queue<pi, vpi, greater<pi>> pq;
        queue<int> q;
        vvi edges;
        rep(i, 0, n){
            // for(int j : adj[i]){
                edges.pb({arr[i], i});
            // }
        }
        sort(all(edges));
        rep(i, 0, sz(edges)){
            if(arr[uf.find(edges[i][1])] == 0){
                for(int j : adj[edges[i][1]]){
                    if(!uf.sameSet(edges[i][1], j) && uf.size(edges[i][1]) >= arr[j]){
                        uf.join(edges[i][1], j);
                    }
                }
            }
            for(int j : adj[edges[i][1]]){
                if(!uf.sameSet(edges[i][1], j) && uf.size(j) >= arr[edges[i][1]] && arr[uf.find(j)] == 0){
                    uf.join(edges[i][1], j);
                }
            }
            // int siz = max(arr[uf.find(edges[i][1])] == 0 ? uf.size(edges[i][1]) : 0, arr[uf.find(edges[i][2])] == 0 ? uf.size(edges[i][2]) : 0);
            // if(!uf.sameSet(edges[i][2], edges[i][1]) && siz >= edges[i][0]){
            //     uf.join(edges[i][2], edges[i][1]);
            //     // pq.push({arr[j], j});
            // }

        }
        // // int numpd = 0;
        // rep(i, 0, n){
        //     if(arr[i] == 0){
        //         // qd[i] = true;
        //         // q.push(i);
        //         pq.push({arr[i], i});
        //     }
        // }
        // while(!pq.empty()){
        //     pi p = pq.top(); pq.pop();
        //     for(int j : adj[p.s]){
        //         if(!uf.sameSet(p.s, j) && max(uf.size(p.s), uf.size(j)) >= max(arr[p.s], arr[j])){
        //             uf.join(p.s, j);
        //             pq.push({arr[j], j});
        //         }
        //     }
        // }
        rep(i, 0, n){
            if(uf.size(i) >= n){
                winnable = true;
            }
        }
        cout << (winnable ? "YES": "NO") << nL;
    }
    
    return 0;
}
