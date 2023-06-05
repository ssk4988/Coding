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
    int n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    vi a(n);
    rep(i, 0, n)
    {
        if (str[i] == '(') a[i] = 1;
        else a[i] = -1;
    }
    if(n % 2 == 1){
        rep(i, 0, q){cin >> n; cout << "NO\n";}
        return 0;
    }
    set<int> posdouble, negdouble;
    rep(i, 0, n - 1)
    {
        if (a[i] == 1 && a[i + 1] == 1) posdouble.insert(i);
        if (a[i] == -1 && a[i + 1] == -1) negdouble.insert(i);
    }
    rep(i, 0, q)
    {
        int idx;
        cin >> idx;
        idx--;
        if (idx && a[idx] == 1 && a[idx - 1] == 1) posdouble.erase(idx - 1);
        if (idx && a[idx] == -1 && a[idx - 1] == -1) negdouble.erase(idx - 1);
        if (idx + 1 < n && a[idx] == 1 && a[idx + 1] == 1) posdouble.erase(idx);
        if (idx + 1 < n && a[idx] == -1 && a[idx + 1] == -1) negdouble.erase(idx);
        if (a[idx] == 1) a[idx] -= 2;
        else a[idx] += 2;
        if (idx && a[idx] == 1 && a[idx - 1] == 1) posdouble.insert(idx - 1);
        if (idx && a[idx] == -1 && a[idx - 1] == -1) negdouble.insert(idx - 1);
        if (idx + 1 < n && a[idx] == 1 && a[idx + 1] == 1) posdouble.insert(idx);
        if (idx + 1 < n && a[idx] == -1 && a[idx + 1] == -1) negdouble.insert(idx);
        int firstdoublepos = posdouble.size() ? *posdouble.begin() : n;
        int lastdoublepos = posdouble.size() ? *posdouble.rbegin() : -1;
        int firstdoubleneg = negdouble.size() ? *negdouble.begin() : n;
        int lastdoubleneg = negdouble.size() ? *negdouble.rbegin() : -1;
        if(firstdoublepos <= firstdoubleneg && lastdoublepos <= lastdoubleneg && a[0] == 1 && a[n - 1] == -1) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
