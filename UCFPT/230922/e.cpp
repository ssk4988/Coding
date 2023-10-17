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

vvi matmul(vvi &a, vvi &b){
    vvi res(sz(a), vi(sz(b[0])));
    rep(i, 0, sz(res)){
        rep(j, 0, sz(res[i])){
            rep(k, 0, sz(a[i])){
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % 37;
            }
        }
    }
    return res;
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi a(n, vi(n));
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> a[i][j];
        }
    }
    auto cv = [](char c)->int{
        if(c == ' ') return 36;
        if(c >= 'A' && c <= 'Z') return c - 'A';
        return c - '0' + 26;
    };
    auto rv = [](int v)->char{
        if(v < 26) return 'A' + v;
        if(v < 36) return '0' - 26 + v;
        return ' ';
    };
    string message;
    getline(cin, message);
    getline(cin, message);
    while(sz(message) % n) message.pb(' ');
    // cout << message << "'" << nL;
    for(int j = 0; j < sz(message); j += n){
        vvi m;
        rep(i, 0, n){
            m.pb({cv(message[j + i])});
        }
        vvi res = matmul(a, m);
        rep(i, 0, sz(res)){
            cout << rv(res[i][0]);
        }
    }
    cout << nL;

    return 0;
}
