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

int getID(int node, int teacher, bool negated){
    return node * 6 + 2 * teacher + negated;
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


void disjoint(int k1, int k2){
    rep(teacher, 0, 3){
        // notequal(getID(k1, teacher, false), getID(k2, teacher, false));
        implies(getID(k1, teacher, false), getID(k2, teacher, true));
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    // li_j represents whether kid i has teacher j
    vvi ranks(n);
    vi tc(n);
    rep(i, 0, n){
        cin >> tc[i];
        ranks[i].resize(n - 1);
        rep(j, 0, sz(ranks[i])){
            cin >> ranks[i][j];
            ranks[i][j]--;
        }
    }
    int lo = n;
    rep(mid, 0, n){
    // int lo = 0, hi = n - 1;
    // while(lo < hi){
        // int mid = lo + (hi - lo) / 2;
        adj = vector<set<int>>(6 * n);
        cdx.assign(6 * n, -1);
        rep(i, 0, n){
            setbool(getID(i, tc[i], false), false);
            rep(j, 0, 3){
                if(j == tc[i]) continue;
                rep(j1, j + 1, 3){
                    if(j1 == tc[i]) continue;
                    notequal(getID(i, j, false), getID(i, j1, false));
                }
            }
            rep(j, mid, n - 1){
                disjoint(i, ranks[i][j]);                
            }
        }
        scc(adj, setscc);
        bool works = true;
        rep(i, 0, sz(cdx)){
            if(cdx[i] == cdx[i^1] && cdx[i] != -1){
                works = false;
            }
        }
        // cout << "tried " << mid << nL;
        if(works){
            // cout << mid << " works" << nL;
            // cout << "configuration: =============" << nL;
            // rep(i, 0, sz(cdx)){
            //     if(i % 2 == 1) continue;
            //     if(cdx[i] < cdx[i + 1]){
            //         int id = i / 6;
            //         int teacher = (i % 6) / 2;
            //         cout << "student " << id << " has teacher " << teacher << nL;
            //     }
            // }
            lo = mid;
            break;
        }
    //     if(works){
    //         hi = mid;
    //     }
    //     else{
    //         lo = mid + 1;
    //     }
    // }
    }
    cout << lo << nL;
    
    return 0;
}