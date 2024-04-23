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
int d, w; 

vi extract6(int v){
    vi res;
    rep(i, 0, d){
        res.pb(v % 6);
        v /= 6;
    }
    reverse(all(res));
    return res;
}

int getidx6(vi &v){
    int idx = 0;
    rep(i, 0, d){
        idx = idx * 6 + v[i];
    }
    return idx;
}

vi extract7(int v){
    vi res;
    rep(i, 0, d){
        res.pb(v % 7);
        v /= 7;
    }
    reverse(all(res));
    return res;
}

int getidx7(vi &v){
    int idx = 0;
    rep(i, 0, d){
        idx = idx * 7 + v[i];
    }
    return idx;
}

int conv(char c){
    if('A' <= c && c <= 'Z') return c - 'A';
    return c - '0' + 26;
}
const ld inf = 1e15;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> d >> w;
    vvi dice(d, vi(6));
    rep(i, 0, d){
        string str; cin >> str;
        rep(j, 0, 6){
            dice[i][j] = conv(str[j]);
        }
    }
    set<vi> words;
    rep(i, 0, w){
        vi freq(36);
        string str; cin >> str;
        for(char c : str) freq[conv(c)]++;
        words.insert(freq);
    }
    int n6 = 1, n7 = 1;
    rep(i, 0, d) n6 *= 6;
    rep(i, 0, d) n7 *= 7;
    cout << n6 << " " << n7 << endl;
    vector<vd> ans(9, vd(n6, inf));
    vvi rollprecomp6(n6), rollprecomp7(n7);
    rep(i, 0, n6) rollprecomp6[i] = extract6(i);
    rep(i, 0, n7) rollprecomp7[i] = extract7(i);
    rep(i, 0, n6){
        vi freq(36);
        rep(j, 0, d){
            freq[dice[j][rollprecomp6[i][j]]]++;
        }
        if(words.count(freq)) {
            cout << "word: ";
            rep(j, 0, 36) if(freq[j]) cout << j << ",";
            cout << " dice: ";
            rep(j, 0, d) cout << rollprecomp6[i][j] << ",";
            cout << endl;
            ans[0][i] = 1;
        }
    }
    vector<vd> precomp(sz(ans), vd(n7));
    rep(iter, 0, sz(ans)-1){
        vector<vd> layers(d+1, vd(n7));
        rep(i, 0, n6){
            layers[0][getidx7(rollprecomp6[i])] = ans[iter][i];
        }
        rep(layer, 0, d){
            rep(i, 0, n7){
                if(rollprecomp7[i][layer] == 6){
                    vi cur = rollprecomp7[i];
                    rep(j, 0, 6){
                        cur[layer] = j;
                        layers[layer+1][i] += layers[layer][getidx7(cur)];
                    }
                } else layers[layer+1][i] += layers[layer][i];
            }
        }
        rep(i, 0, n6){
            ld best = inf;
            rep(mask, 0, 1 << d){
                vi cur = rollprecomp7[i];
                rep(j, 0, d){
                    if((mask >> j) & 1) cur[j] = 6;
                }
                ld ans = layers.back()[getidx7(cur)];
                rep(j, 0, d) if((mask >> j) & 1) ans /= 6;
                best = min(best, ans);
            }
            ans[iter+1][i] = best;
        }
    }
    ld res = 0;
    rep(i, 0, n6) res += ans.back()[i];
    res /= n6;
    cout << fixed << setprecision(8) << res << "\n";
    
    return 0;
}
