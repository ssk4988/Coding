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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret, dep;
	RMQ<int> rmq;

	LCA(vector<vi>& C, int root) : time(sz(C)), dep(sz(C)), rmq((dfs(C,root,-1, 0), ret)) {}
	void dfs(vector<vi>& C, int v, int par, int d) {
		time[v] = T++;
        dep[v] = d;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v, d + 1);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

string num(int k){
    string res = to_string(k);
    if(k % 100 >= 10 && k % 100 < 20){
        res.append("th");
    }
    else if(k % 10 == 1) res.append("st");
    else if(k % 10 == 2) res.append("nd");
    else if(k % 10 == 3) res.append("rd");
    else res.append("th");
    return res;
}
string prtime(int k){
    if(k != 1) return "times";
    else return "time";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    map<string, int> rl;
    vvi child;
    rep(i, 0, n){
        string str; int k; cin >> str >> k;
        if(rl.count(str) == 0){
            child.pb({});
            rl[str] = sz(rl);
        }
        rep(j, 0, k){
            string des; cin >> des;
            if(rl.count(des) == 0){
                rl[des] = sz(rl);
                child.pb({});
            }
            child[rl[str]].pb(rl[des]);
        }
    }
    n = sz(child);
    vi par(n, -1);
    rep(i, 0, n){
        for(int j : child[i]) par[j] = i;
    }
    int root = -1;
    rep(i,0,n){
        if(par[i] == -1) root = i;
    }
    // cout << root << nL;
    LCA l(child, root);
    rep(i, 0, q){
        string s1, s2; cin >> s1 >> s2;
        int a = rl[s1], b = rl[s2];
        // cout << s1 << " " << s2 << nL;
        int lc = l.lca(a, b);
        int da = l.dep[a] - l.dep[lc], db = l.dep[b] - l.dep[lc];
        if(min(da, db) == 0){
            if(da > db){
                swap(da, db);
                swap(a, b);
                swap(s1, s2);
            }
            if(db == 1){
                cout << s2 << " is the child of " << s1 << nL;
            }
            else{
                cout << s2 << " is the ";
                rep(i, 0, db - 2){
                    cout << "great ";
                }
                cout << "grandchild of " << s1 << nL;
            }
        }
        else if(da == db){
            if(da == 1){
                cout << s1 << " and " << s2 << " are siblings" << nL;
            }
            else{
                cout << s1 << " and " << s2 << " are " << num(da - 1) << " cousins" << nL;
            }
        }
        else{
            if(da > db) swap(da, db);
            cout << s1 << " and " << s2 << " are " << num(da - 1) << " cousins, " << to_string(db - da) << " " << prtime(db - da) << " removed" << nL;
        }
    }


    
    return 0;
}
