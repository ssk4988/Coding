#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef vector<vi> vvi;
typedef vector<pii> vii;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i = a; i < b; i++)
#define nl '\n'

const int DEBUG = false;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n; 
    vi ray (n);
    vi prefixMod (3);
    prefixMod[0]++;
    vector<vvi> freq(3, vvi(3, vi(3)));
    int curW = 0, curPSum = 0;
    ll ans = 0;
    freq[curW][curPSum][0]++;
    for(int i = 0; i < n; i++) 
    {
        cin >> ray[i];
        ray[i] %= 3;
        rep(w, 0, 3){
            rep(p, 0, 3){
                vi rot(3);
                rep(op, 0, 3){
                    rot[(op + ray[i]) % 3] = freq[w][p][op];
                }
                rep(op, 0, 3){
                    freq[w][p][op] = rot[op];
                }
            }
        }
        curW = (curW + ray[i] * curPSum) % 3;
        curPSum = (curPSum + ray[i]) % 3;
        rep(w, 0, 3){
            rep(p, 0, 3){
                rep(op, 0, 3){
                    int rval = (w + p * op) % 3;
                    if(rval == curW){
                        if(DEBUG && freq[w][p][op] > 0) { 
                            cout << "at index " << i << ", w(1,L)=" << w << " pref(1,L)=" << p << ", pref(L+1,R)=" << op << nl;
                        }
                        ans += freq[w][p][op];
                    }
                }
            }
        }
        freq[curW][curPSum][0]++;

        if(DEBUG)
        {
            cout << "ray[" << i << "] = " << ray[i] << nl;
            cout << "curW prefix is " << curW << nl;
            cout << "curPSum is " << curPSum << nl;
        }
    }
    curW = 0, curPSum = 0;
    // for(int i = n - 1; i >= 0; i--){
    //     curW = (curW + ray[i] * curPSum) % 3;
    //     curPSum = (curPSum + ray[i]) % 3;
    //     if(curW == 0){
    //         ans++;
    //     }
    // }
    // rep(w, 0, 3){
    //     rep(p, 0, 3){
    //         rep(op, 0, 3){
    //             int rval = (w + p * op) % 3;
    //             if(rval == curW){
    //                 if(DEBUG && freq[w][p][op] > 0) { 
    //                     cout << "at index " << n << ", w(1,L)=" << w << " pref(1,L)=" << p << ", pref(L+1,R)=" << op << nl;
    //                 }
    //                 ans += freq[w][p][op];
    //             }
    //         }
    //     }
    // }

    cout << ans << nl;
}