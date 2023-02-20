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

vi num, st;
vector<vector<pi>> ed;
int Time;
vector<bool> art;
vi numchild;
template <class F>
int dfs(int at, int par, F &f)
{
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at])
        if (pa.second != par)
        {
            tie(y, e) = pa;
            if (num[y])
            {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.push_back(e);
            }
            else
            {
                numchild[at]++;
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up < me)
                    st.push_back(e);
                else
                { // (up == me) {
                    art[at] = true;
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                }
                // else { /* e is a bridge */}
            }
        }
    return top;
}

map<int, int> cc;
int cnt = 0;
int n;
int bccid = 0;
vpi edg;
vi bcclabel;

void func(vi bcce){
    rep(i, 0, sz(bcce)){
        bcclabel[bcce[i]] = bccid;
    }
    bccid++;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int cn = 0;
    while(true){
        cin >> n;
        cn++;
        if(n == 0) break;
        cc.clear();Time = 0;cnt = 0;
        edg = vpi(n);
        bccid = 0;
        bcclabel = vi(n, -1);
        rep(i, 0, n){
            int a, b; cin >> a >> b;
            a--,b--;
            if(cc.find(a) == cc.end()){
                cc[a] = cnt++;
            }
            if(cc.find(b) == cc.end()){
                cc[b] = cnt++;
            }
            a = cc[a];
            b = cc[b];
            edg[i] = {a, b};
        }
        art = vector<bool>(cnt);
        numchild = vi(cnt);
        ed = vector<vector<pi>>(cnt);
        rep(i, 0, n){
            ed[edg[i].f].pb({edg[i].s, i});
            ed[edg[i].s].pb({edg[i].f, i});
        }
        num=vi(sz(ed), 0);
        rep(i, 0, sz(ed)) if (!num[i])
            dfs(i, -1, func); // create function
        art[0] = numchild[0] > 1;
        vector<set<int>> bccset(bccid);
        rep(i, 0, n){
            bccset[bcclabel[i]].insert(edg[i].f);
            bccset[bcclabel[i]].insert(edg[i].s);
        }
        int totart = 0;
        rep(i, 0, cnt){
            if(art[i]) totart++;
        }
        ll ans = 0, ways = 1;
        rep(i, 0, bccid){
            int numart = 0, nonart = 0;
            for(int j : bccset[i]){
                if(art[j]) numart++;
                else nonart++;
            }
            if(numart == 1){
                ans++;
                ways *= nonart;
            }
            assert(numart > 0 || totart == 0);
        }
        if(totart == 0){
            ll lower = cnt;
            ll upper = cnt - 1;
            if(lower % 2 == 0){
                lower /= 2;
            }
            else{
                upper /= 2;
            }
            ways = lower * upper;
            ans = 2;
        }
        cout << "Case " << cn << ": " << ans << " " << ways << nL;
    }
    
    return 0;
}
