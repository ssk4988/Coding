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

vector<int> prefix_function(vi str) {
    int n = (int)str.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && str[i] != str[j])
            j = pi[j-1];
        if (str[i] == str[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi a(2, vi(n));
    rep(i, 0, 2){
        rep(j, 0, n){
            cin >> a[i][j];
        }
        sort(all(a[i]));
    }
    vvi m(2, vi(n));
    int ni;
    rep(i, 0, 2){
        rep(j, 0, n){
            ni = j + 1;
            if(ni == n) ni = 0;
            m[i][j] = a[i][ni] - a[i][j];
            if(m[i][j] < 0) m[i][j] += 360000;
        }
    }
    vi c;
    c.insert(c.end(), all(m[0]));
    c.pb(7000000);
    c.insert(c.end(), all(m[1]));
    c.insert(c.end(), all(m[1]));
    vi c1 = prefix_function(c);
    bool works = false;
    rep(i, 0, c1.size()){
        if(c1[i] == n){
            works = true;
        }
    }
    cout << (works ? "" : "im") << "possible" << nL;
    
    return 0;
}