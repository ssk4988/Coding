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
    int n, l;
    cin >> n >> l;
    string s1;
    getline(cin, s1);
    l--;
    char c;
    vector<vector<char>> a(n);
    while (getline(cin, s1) && l-- && s1[1] != '1')
    {
        rep(i, 0, s1.size()){
            if(i % 4 == 1 && s1[i] != ' '){
                a[i / 4].pb(s1[i]);
            }
        }
    }
    rep(i, 0, n){
        reverse(all(a[i]));
    }
    getline(cin, s1);
    l--;
    rep(j, 0, l){
        cin >> s1;
        int q, b1, b; cin >> q >> s1 >> b1 >> s1 >> b;
        b1--;b--;
        vi temp;
        rep(i, 0, q){
            temp.pb(a[b1].back());
            a[b1].pop_back();
        }
        rep(i, 0, q){
            a[b].pb(temp.back());
            temp.pop_back();
        }
    }
    rep(i, 0, n){
        cout << a[i].back();
    }
    cout << nL;

    


    return 0;
}