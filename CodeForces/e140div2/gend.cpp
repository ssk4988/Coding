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
int n, n1;
string str;
vector<bool> canwin;

void gen(vi &perm, vector<bool> &used){
    if(perm.size() == n){
        vi cur(perm);
        for(int j = 0; j < n1; j++){
            vi ncur;
            for(int i = 0; i < cur.size(); i+= 2){
                if(str[j] == '1') ncur.pb(max(cur[i], cur[i + 1]));
                else ncur.pb(min(cur[i], cur[i + 1]));
            }
            cur = ncur;
        }
        canwin[cur[0]] = true;
        return;
    }
    for(int i = 0; i < n; i++){
        if(used[i]) continue;
        used[i] = true;
        perm.pb(i);
        gen(perm, used);
        used[i] = false;
        perm.pop_back();
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    cin >> n1 >> str;
    n = 1 << n1;
    canwin.resize(n);
    vector<bool> used(n, false);
    vi perm;
    gen(perm, used);
    rep(i, 0, n){
        if(canwin[i]) cout << (i + 1) << " ";
    }
    cout << nL;
    return 0;
}