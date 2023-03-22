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

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

int r, c;
vvi ds = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int getID(int row, int col, int dir, bool negate){
    return negate + 2 * dir + 2 * 4 * col + 2 * 4 * c * row;
}

vi cdx;
// try vector afterward
vector<set<int>> adj;
void setscc(vi &v){
    for(int i : v){
        cdx[i] = ncomps;
    }
}

void setbool(int id, bool v){
    int otherid = id ^ 1;
    if(v){
        adj[otherid].insert(id);
    }
    else{
        adj[id].insert(otherid);
    }
}

void implies(int id1, int id2){
    adj[id1].insert(id2);
    adj[id2^1].insert(id1^1);
}

void notequal(int id1, int id2){
    adj[id1].insert(id2^1);
    adj[id1^1].insert(id2);
    adj[id2].insert(id1^1);
    adj[id2^1].insert(id1);
}

bool DEBUG = false;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cin >> r >> c;
        vector<vector<char>> grid(r, vector<char>(c));
        adj.clear();
        adj.resize(r * c * 4 * 2);
        cdx.assign(r * c * 4 * 2, -1);
        rep(i, 0, r){
            string str; cin >> str;
            rep(j, 0, c){
                grid[i][j] = str[j];
            }
        }
        rep(i, 0, r){
            rep(j, 0, c){
                if(grid[i][j] == 'W'){
                    vector<bool> isblack(4);
                    vector<bool> istrue(4);
                    rep(k, 0, 4){
                        int i1 = i + ds[k][0], j1 = j + ds[k][1];
                        if(i1 < 0 || i1 >= r || j1 < 0 || j1 >= c){
                            continue;
                        }
                        if(grid[i1][j1] == 'B'){
                            isblack[k] = true;
                            int i2 = i1 + ds[k][0], j2 = j1 + ds[k][1];
                            if(i2 < 0 || i2 >= r || j2 < 0 || j2 >= c){
                                if(DEBUG) cout << i << ", " << j << " in dir " << k << " must be true" << nL;
                                setbool(getID(i, j, k, false), true);
                                istrue[k] = true;
                            }
                            else{
                                if(DEBUG) cout << "add notequal from " << i << ", " << j << " to " << i2 << ", " << j2 << nL;
                                notequal(getID(i, j, k, false), getID(i2, j2, k + 2, false));
                            }
                        }
                        else{
                            if(DEBUG) cout << i << ", " << j << " in dir " << k << " must be false" << nL;
                            setbool(getID(i, j, k, false), false);
                        }
                    }
                    rep(k, 0, 2){
                        if(isblack[k] && isblack[k + 2]){
                            int i1 = i + ds[k][0], j1 = j + ds[k][1];
                            int i2= i + ds[k+2][0], j2 = j + ds[k+2][1];
                            notequal(getID(i, j, k, false), getID(i, j, k + 2, false));
                        }
                    }
                    rep(k, 0, 4){
                        if(!istrue[k]) continue;
                        rep(l, k + 1, 4){
                            if(!istrue[l]) continue;
                            notequal(getID(i, j, k, false), getID(i, j, l, false));
                        }
                    }
                }
            }
        }
        scc(adj, setscc);
        bool works = true;
        rep(i, 0, sz(cdx)){
            if(i % 2 == 1) continue;
            if(cdx[i] == cdx[i + 1]){
                works = false;
            }
        }
        cout << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}