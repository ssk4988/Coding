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
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
        a[i] -= (i+1);
    }
    priority_queue<pi, vpi, greater<pi>> pq;
    set<int> ss;
    vvi best(n, vi(2, n));
    for(int i = n - 1; i >= 0; i--){
        pq.push({a[i], i});
        while(sz(pq)){
            auto [val, idx] = pq.top();
            if(val >= -i) break;
            pq.pop();
            ss.insert(idx);
        }
        int pnt = 0;
        for(int idx : ss){
            if(pnt >= sz(best[i])) break;
            best[i][pnt] = idx;
            pnt++;
        }
    }
    vl bestsum(n+1), bestsum2(n+1);
    ll sub = 0;
    rep(i, 0, n){
        sub += i;
        bestsum[i+1] = bestsum[i] + best[i][0];
        bestsum2[i+1] = bestsum2[i] + best[i][1];
    }
    int q; cin >> q;
    rep(_, 0, q){
        int i, x; cin >> i >> x; i--;
        x -= i+1;
        int first = -1; // min index where i could be the best guy
        for(int dif = 1 << 20; dif; dif /= 2){
            int cur = first + dif;
            if(cur < n && best[cur][0] < i) first = cur;
        }
        first++;
        int last = first - 1; // exclusive, after last where i am the best
        for(int dif = 1 << 20; dif; dif /= 2){
            int cur = last + dif;
            if(cur < n && cur <= i && i <= best[cur][0] && x < -cur) last = cur;
        }
        last++;
        int amend = last;
        last = first - 1; // exclusive, after last where i was the best
        for(int dif = 1 << 20; dif; dif /= 2){
            int cur = last + dif;
            if(cur < n && cur <= i && i == best[cur][0]) last = cur;
        }
        last++;
        int wasend = last;
        ll ans = bestsum[n] - bestsum[max(wasend, amend)] + bestsum[first] - bestsum[0];
        ans += ll(i) * (amend - first);
        if(amend <= wasend){
            ans += bestsum2[wasend] - bestsum2[amend];
        }
        ans -= sub;
        cout << ans << "\n";
    }
    
    return 0;
}
