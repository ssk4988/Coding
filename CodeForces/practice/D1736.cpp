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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(2 * n);
        vi s;
        vi frq(2);
        rep(i, 0, 2 * n){
            char c; cin >> c;
            a[i] = c - '0';
            frq[a[i]]++;
        }
        if((frq[0] % 2 == 1) || frq[1] % 2 == 1){
            cout << "-1\n";
            continue;
        }
        int val = -1;
        for(int i = 0; i < 2 * n; i += 2){
            if(a[i] == a[i + 1]) continue;
            if(sz(s) == 0){
                s.pb(i);
                val = a[i];
            }
            else{
                int re = a[i] == val ? i + 1 : i;
                s.pb(re);
                swap(val, a[re]);
            }
        }
        if(sz(s)) a[s[0]] = val;
        // cout << "for case " << cn << ":\n";
        cout << sz(s) << " ";
        for(int i : s) cout << (i + 1) << " ";
        cout << "\n";
        string str;
        for(int i = 0; i < 2 * n; i += 2){
            // str.pb('0' + a[i]);
            cout << (i + 1) << " ";
        }

        // rep(i, 0, 2 * n){
        //     str.pb('0' + a[i]);
        // }
        cout << "\n";
        // cout << "finished case " << cn << endl;
        // cout << "DEBUG: " << str << "\n";

    }
    
    return 0;
}
