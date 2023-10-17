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

string str;
void bt(int idx, string &cur){
    if(sz(str) == idx){
        cout << cur << nL;
        return;
    }
    cur.pb(tolower(str[idx]));
    bt(idx + 1, cur);
    cur.pop_back();
    if(idx + 2 <= sz(str) && str[idx] == 'S' && str[idx + 1] == 'S'){
        cur.pb('B');
        bt(idx + 2, cur);
        cur.pop_back();
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> str;
    string cur;
    bt(0, cur);
    return 0;
}
