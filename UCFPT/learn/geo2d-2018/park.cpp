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
    int n, m;
    while(true){
        cin >> n >> m;
        vpi p;
        if(n == 0 && m == 0) break;
        vi visible(n);
        vpi x, y;
        rep(i, 0, n){
            int x1, y1; cin >> x1 >> y1;
            p.pb({x1, y1});
            x.pb({x1, i});
            y.pb({y1, i});
        }
        rep(i, 0, m){
            string str; cin >> str;
            int c = stoi(str.substr(2));
            bool isx = str[0] == 'x';
            (isx ? x : y).pb({c, -1});
        }
        sort(all(x)); sort(all(y));
        ll lastv = LLONG_MIN;
        map<int, int> pre;
        rep(i, 0, sz(x)){
            if(x[i].s != -1){
                if(lastv != LLONG_MIN && (pre.count(p[x[i].s].s) == 0 || pre[p[x[i].s].s] <= lastv)){
                    visible[x[i].s] = true;
                }
                pre[p[x[i].s].s] = x[i].f;
            }
            else{
                lastv = x[i].f;
            }
        }
        reverse(all(x));
        pre.clear();
        lastv = LLONG_MAX;
        rep(i, 0, sz(x)){
            if(x[i].s != -1){
                if(lastv != LLONG_MAX && (pre.count(p[x[i].s].s) == 0 || pre[p[x[i].s].s] >= lastv)){
                    visible[x[i].s] = true;
                }
                pre[p[x[i].s].s] = x[i].f;
            }
            else{
                lastv = x[i].f;
            }
        }
        pre.clear();
        lastv = LLONG_MIN;
        rep(i, 0, sz(y)){
            if(y[i].s != -1){
                if(lastv != LLONG_MIN && (pre.count(p[y[i].s].f) == 0 || pre[p[y[i].s].f] <= lastv)){
                    visible[y[i].s] = true;
                }
                pre[p[y[i].s].f] = y[i].f;
            }
            else{
                lastv = y[i].f;
            }
        }
        reverse(all(y));
        pre.clear();
        lastv = LLONG_MAX;
        rep(i, 0, sz(y)){
            if(y[i].s != -1){
                if(lastv != LLONG_MAX && (pre.count(p[y[i].s].f) == 0 || pre[p[y[i].s].f] >= lastv)){
                    visible[y[i].s] = true;
                }
                pre[p[y[i].s].f] = y[i].f;
            }
            else{
                lastv = y[i].f;
            }
        }
        int cnt= 0;
        rep(i, 0, n){
            if(visible[i])cnt++;
        }
        cout << cnt << nL;
    }
    
    return 0;
}