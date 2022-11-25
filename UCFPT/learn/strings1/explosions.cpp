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
    string str, exp; cin >> str >> exp;
    string comb = exp + "#" + str;
    int n = (int)comb.length();
    vector<int> pi;
    vector<int> ind;
    ind.pb(0);
    pi.pb(0);
    int tar = exp.length();
    for (int i = 1; i < n; i++) {
        int j = pi[pi.size() - 1];
        while (j > 0 && comb[i] != comb[j])
            j = pi[j-1];
        if (comb[i] == comb[j])
            j++;
        pi.pb(j);
        ind.pb(i);
        if(pi[pi.size() - 1] == tar){
            rep(j, 0, tar){
                pi.pop_back();
                ind.pop_back();
            }
        }
    }
    if(ind.size() <= tar + 1){
        cout << "FRULA" << nL;
    }
    else{
        rep(i, tar + 1, ind.size()){
            cout << comb[ind[i]];
        }
        cout << nL;
    }
    
    return 0;
}