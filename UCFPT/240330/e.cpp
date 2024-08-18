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
    int n, m; cin >> n >> m;
    int t = 1;
    vvi child(t);
    vi a(n);
    vi priority(t), order(t), depth(t); // lower priority means bigger
    auto cmp = [&](int a, int b) -> bool { // compare to determine priorities
        if(depth[a] != depth[b]) return depth[a] > depth[b];
        rep(i, 0, min(sz(child[a]), sz(child[b]))){
            if(child[a][i] != child[b][i]) return priority[child[a][i]] < priority[child[b][i]];
        }
        return sz(child[a]) > sz(child[b]);
    };
    auto cmpprior = [&](int a, int b) -> bool {
        return priority[a] < priority[b];
    };
    rep(_, 0, m){
        char c; cin >> c;
        if(c == '!'){
            int i, j; cin >> i >> j; i--, j--;
            int x = t;
            t++;
            child.push_back(child[a[i]]);
            child[x].insert(lower_bound(all(child[x]), a[j], cmpprior), a[j]);
            depth.pb(max(depth[a[i]], 1 + depth[a[j]]));
            a[i] = x;
            int insidx = lower_bound(all(order), x, cmp) - order.begin();
            int endidx = upper_bound(all(order), x, cmp) - order.begin();
            if(insidx != endidx){
                a[i] = order[insidx];
                t--;
                depth.pop_back();
                child.pop_back();
                continue;
            }
            order.insert(order.begin() + insidx, x);
            priority.pb(-1);
            rep(i, 0, sz(order)){
                priority[order[i]] = i;
            }
        }
        else{
            int i, j; cin >> i >> j; i--, j--;
            int pi = priority[a[i]], pj = priority[a[j]];
            if(pi == pj){
                cout << "=\n";
            }
            else if(pi < pj) cout << ">\n";
            else cout << "<\n";
        }
    }
    
    return 0;
}