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
    int n,k; cin >> n >> k;
    map<int, int> freq;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi ans;
    if(k == 1){
        ans = a;
    }
    else{

        pi cur = {-1, (k + 1) / 2};
        rep(i, 0, k){
            freq[a[i]]++;
        }
        for(auto &p : freq){
            if(p.s >= cur.s){
                cur.f = p.f;
                break;
            }
            cur.s -= p.s;
        }
        ans.pb(cur.f);
        rep(i, k, n){
            int change = 0;
            if(a[i] >= cur.f){
                change++;
            }
            else{
                change--;
            }
            if(a[i - k] >= cur.f){
                change--;
            }
            else{
                change++;
            }
            freq[a[i]]++;
            freq[a[i - k]]--;
            while(cur.s > freq[cur.f]){
                cur.s -= freq[cur.f];
                auto it = freq.find(cur.f);
                it = next(it);
                cur.f = (*it).f;
            }
            if(change > 0){
                cur.s++;
            }
            if(change < 0){
                cur.s--;
            }
            while(cur.s > freq[cur.f]){
                cur.s -= freq[cur.f];
                auto it = freq.find(cur.f);
                it = next(it);
                cur.f = (*it).f;
            }
            while(cur.s < 1){
                auto it = freq.find(cur.f);
                it = prev(it);
                cur.f = (*it).f;
                cur.s += freq[cur.f];
            }
            if(freq[a[i - k]] == 0){
                freq.erase(a[i - k]);
            }
            ans.pb(cur.f);
        }
    }
    rep(i, 0, sz(ans)){
        cout << ans[i] << " ";
    }
    cout << nL;
    
    return 0;
}
