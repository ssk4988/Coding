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
    int n, k; cin >> n >> k;
    string s1, s2; cin >> s1 >> s2;
    vi v1(n), v2(n), pref2(n);
    deque<pi> dq; // {color, start}
    int ans = 0;
    vi qs;
    rep(i, 0, n){
        v1[i] = s1[i] == 'B';
        pref2[i] = v2[i] = s2[i] == 'B';
        if(i) pref2[i] += pref2[i - 1];
        if(v1[i] != v2[i]){
            qs.pb(i);
        }
    }
    auto pref = [&](int l, int r)->int{
        int val = pref2[r];
        if(l >= 0) val -= pref2[l];
        return val;
    };
    vi covered(n, -1);
    rep(i, 0, n){
        if(covered[i]) continue;
        if(v1[i] != v2[i]){
            for(int j = i - 1; j >= 0 && !covered[j] && v2[j] == v2[i]; j--){
                covered[j] = i;
            }
            for(int j = i; j < n && !covered[j] && v2[j] == v2[i]; j++){
                covered[j] = i;
            }
        }
    }
    int pre = -1;
    vi places;
    rep(i, 0, n){
        assert(sz(dq) <= 2);
        while(sz(dq) && dq.front().s + k <= i){
            dq.pop_front();
        }
        if(sz(dq) && dq.back().f != v2[i] && covered[i] == -1) dq.pop_back();
        if(sz(dq) == 2){
            if(dq.back().f != v2[i]) dq.pop_back();
            
        }
        if(sz(dq) == 0){
            ans++;
            dq.pb({v2[i], i});
        }
        if(sz(dq)){
            if(dq.back().f != v2[i]){
                if(covered[i] == -1) dq.pop_back();
                else{
                    ans++;
                    dq.pb({v2[i], i});
                }
            }
        }
        if(v2[i] == v1[i]){
            else{
                
            }
            
            continue;
        }
        if(sz(dq) == 0){
            ans++;
            dq.pb({v2[i], i});
        }
        else if(v2[i] == dq.back().f){
            if(pref(dq.back().s, i) == (i - dq.back().s) * v2[i]){
                // same color so far so extend
            }
            else{
                ans++;
                dq.pop_back();
                dq.pb({v2[i], i});
            }
        }
        else{
            if(sz(dq) == 1){
                ans++;
                dq.pb({v2[i], i});
            }
            else if(sz(dq) == 2){
                dq.pop_back();
                // extended dq[0]
            }
            else{
                assert(false);
            }
        }
        pre = i;
    }
    cout << ans << "\n";
    
    return 0;
}