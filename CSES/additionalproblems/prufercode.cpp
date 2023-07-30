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
    int n; cin >> n;
    vi occ(n + 1);
    vi list(n - 2);
    rep(i, 0, n - 2){
        cin >> list[i];
        list[i]--;
        occ[list[i]]++;
    }
    set<int> leaves;
    rep(i, 0, n){
        if(occ[i] == 0) leaves.insert(i);
    }
    rep(i, 0, n - 2){
        int nex = *leaves.begin();
        leaves.erase(nex);
        cout << (nex + 1) << " " << (list[i] + 1) << nL;
        occ[list[i]]--;
        if(occ[list[i]] == 0) leaves.insert(list[i]);
    }
    assert(sz(leaves) == 2);
    int v = *leaves.begin(), v1 = *leaves.rbegin();
    cout << (v + 1) << " " << (v1 + 1) << nL;

    
    return 0;
}