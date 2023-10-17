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



// vvi jmp, sjmp;
const int lgn = 20;
const int maxn = 2e5 + 10;
int jmp[lgn][maxn], sjmp[lgn][maxn];
int depth[maxn];
// vi depth;

void treeJump(vi &P, vi &a)
{
    int on = 1, d = 1;
    while (on < sz(P))
        on *= 2, d++;
    // jmp = vector<vi> (d, P);
    // sjmp = vvi(d, a);
    rep(i, 0, sz(P)){
        jmp[0][i] = P[i];
        sjmp[0][i] = a[i];
    }
    rep(i, 1, d) rep(j, 0, sz(P))
    {
        jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
        sjmp[i][j] = sjmp[i - 1][jmp[i - 1][j]] | sjmp[i - 1][j];
    }
}

// {new node, score from nod to new node, excluding new node}
int jump(int nod, int steps)
{
    rep(i, 0, lgn) if (steps & (1 << i))
    {
        nod = jmp[i][nod];
    }
    return nod;
}

int jumpsc(int nod, int steps)
{
    int sc = 0;
    rep(i, 0, lgn) if (steps & (1 << i))
    {
        sc |= sjmp[i][nod];
        nod = jmp[i][nod];
    }
    return sc;
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int sc;
    a = jump(a, depth[a] - depth[b]);
    if (a == b)
        return a;
    for (int i = lgn; i--;)
    {
        int c = jmp[i][a], d = jmp[i][b];
        if (c != d)
            a = c, b = d;
    }
    return jmp[0][a];
}

// p is path length desired
int scpath(int l, int a, int b, int p){
    if(p == 0) return 0;
    int p1 = depth[a] - depth[l];
    if(p <= p1) return __builtin_popcount(jumpsc(a, p));
    int sc = jumpsc(a, p1);
    int p2 = depth[b] - depth[l];
    p -= p1;
    int k = jump(b, p2 - p + 1);
    sc |= jumpsc(k, p);
    // cout << "scpath " << a << " to " << b << " through " << l << " with length " << p << " yields " << sc << endl;
    return __builtin_popcount(sc);
}

int path(int l, int a, int b, int p){
    if(p == 0) return a;
    int p1 = depth[a] - depth[l];
    if(p <= p1) return jump(a, p);
    int p2 = depth[b] - depth[l];
    p -= p1;
    int k = jump(b, p2 - p + 1);
    return k;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vvi adj(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi p(n);
        auto dfs = [&](int cur, int par, int d, auto &&dfs)->void{
            p[cur] = par;
            depth[cur] = d;
            for(int nex : adj[cur]){
                if(nex == par) continue;
                dfs(nex, cur, d + 1, dfs);
            }
        };
        dfs(0, 0, 0, dfs);
        treeJump(p, a);

        int q; cin >> q;
        rep(i, 0, q){
            int a, b; cin >> a >> b; a--, b--;
            int l = lca(a, b);
            int len = depth[a] + depth[b] - 2 * depth[l] + 1;
            set<int> interesting;
            int start = 1, prevsc = -1;
            int pstart = a;
            int l1 = l;
            int len1 = len;
            while(len > 0){
                l = lca(pstart, b);
                len = depth[pstart] + depth[b] - 2 * depth[l] + 1;
                // int lo = start, hi = len + 1;
                int lo = 1, hi = len + 1;
                // find min where sc > prevsc
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(scpath(l, pstart, b, mid) > prevsc){
                        hi = mid;
                    }
                    else lo = mid + 1;
                }
                if(lo <= len){
                    prevsc = scpath(l, pstart, b, lo);
                    pstart = path(l, pstart, b, lo);
                    interesting.insert(pstart);
                }
                // start += lo + 1;
            }
            pstart = b;
            len = len1;
            start = 1, prevsc = -1;
            while(start <= len){
                l = lca(pstart, a);
                len = depth[pstart] + depth[a] - 2 * depth[l] + 1;
                // int lo = start, hi = len + 1;
                int lo = 1, hi = len + 1;
                // find min where sc > prevsc
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(scpath(l, pstart, a, mid) > prevsc){
                        hi = mid;
                    }
                    else lo = mid + 1;
                }
                if(lo <= len){
                    prevsc = scpath(l, pstart, a, lo);
                    pstart = path(l, pstart, a, lo);
                    interesting.insert(pstart);
                }
                // start += lo + 1;
            }
            len = l1;
            l = l1;
            int ans = 0;
            for(int k : interesting){
                int left = scpath(l, a, b, k);
                int right = scpath(l, b, a, len + 1 - k);
                ans = max(ans, left + right);
            }
            cout << ans << " ";
        }
        cout << nL;
    }

    return 0;
}
