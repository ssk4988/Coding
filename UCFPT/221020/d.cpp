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

vector<int> prefix_function(string str) {
    int n = (int)str.length();
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
    string str; cin >> str;
    vi pi = prefix_function(str);
    set<int> vals;
    int k = pi.back();
    while(k > 0){
        vals.insert(k);
        k = pi[k - 1];
    }
    int n = str.length();
    int cnt = 0;
    vi qry(n, 0);
    rep(i, 0, n / 2){
        if(vals.find(i + 1) != vals.end()){
            cnt++;
        }
        qry[i + 1] = qry[n - 1 - (i + 1)] = cnt;
    }
    int q; cin >> q;
    rep(i, 0, q){
        int a;
        cin >> a;
        a--;
        cout << qry[a] << nL;
    }
    
    return 0;
}