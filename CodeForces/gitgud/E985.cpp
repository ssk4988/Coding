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
    int n, k, d; cin >> n >> k >> d;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    // int p = -1;
    queue<int> q;
    q.push(0);
    rep(i, 1, n){
        // while(p + 1 <= i && a[i] - a[p+1] > d) p++;
        if(sz(q) && q.front() <= i - k){
            q.push(i); // can transition to new box
        }
        while(sz(q) && a[i] - a[q.front()] > d) q.pop();
    }
    bool works = sz(q) && q.front() <= n - k;
    cout << (works ? "YES" : "NO") << "\n";
    return 0;
}
