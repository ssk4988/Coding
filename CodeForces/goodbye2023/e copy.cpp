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

int n;
ll ans;
vi par, a, pre, in, nex, fnd;
vl lz, score;
vvi child, bucket;
vi path;

bool cmp(int a, int b){
    return pl{score[a], a} > pl{score[b], b}; // reverse order score
}
vector<set<int, decltype(&cmp)>> ss;
void dfs(int u){
    int preval = pre[a[u]];
    if(preval != -1){
        fnd[u] = nex[preval];
        bucket[preval].pb(u);
    }
    pre[a[u]] = u;
    for(int v : child[u]){
        nex[u] = v;
        dfs(v);
    }
    pre[a[u]] = preval;
}

void combset(int u, int v){
    // add ss[v] to ss[u];
    for(int v1 : ss[v]){
        score[v1] = score[v1] + lz[v] - lz[u]; // readjust score
        ss[u].insert(v1);
        // in[v1] = u;
    }
}

void calcdfs(int u){
    lz[u] = 1;
    score[u] = 0;
    ss[u].insert(u);
    // in[u] = u;
    ans = max(ans, 1LL);
    for(int v : child[u]){
        calcdfs(v);
        lz[v]++; // each guy gets new height
    }
    for(int v : bucket[u]){
        ss[fnd[v]].erase(v);
        score[v]--;
        ss[fnd[v]].insert(v);
    }
    vl best(2, 1);
    vi inc;
    inc.pb(*(ss[u].begin()));
    for(int v : child[u]){
        int b = *(ss[v].begin());
        inc.pb(b);
        if(sz(ss[v]) > sz(ss[u])){
            swap(ss[v], ss[u]);
            swap(lz[v], lz[u]);
        }
    }
    for(int v : child[u]){
        combset(u, v);
    }
    for(int c : inc){
        best.pb(score[c] + lz[u]);
    }
    sort(all(best));
    reverse(all(best));
    ans = max(ans, best[0] * best[1]);
}

void solve(){
    // WATCH OUT MEMORY
    cin >> n;
    ans = 0;
    par = vi(n);
    a = vi(n);
    pre = vi(n, -1);
    nex = vi(n);
    fnd = vi(n);
    // in = vi(n);
    lz = vl(n);
    score = vl(n);
    child = vvi(n);
    bucket = vvi(n);
    ss.clear();
    rep(i, 1, n){
        cin >> par[i];
        par[i]--;
        child[par[i]].pb(i);
    }
    rep(i, 0, n){
        cin >> a[i]; a[i]--;
        ss.pb(set<int, decltype(&cmp)>(cmp));
    }
    dfs(0);
    calcdfs(0);
    cout << ans << nL;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    
    return 0;
}
