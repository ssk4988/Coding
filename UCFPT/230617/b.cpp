#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;

const int ALPH = 26;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        vi patch(ALPH);
        rep(i, 0, ALPH) patch[i] = i;
        int p; cin >> p;
        rep(i, 0, p){
            string str; cin >> str;
            int a = str[0] - 'A', b = str[1] - 'A';
            swap(patch[a], patch[b]);
        }
        int d; cin >> d;
        vi lazyrotate(d);
        vvi disk(d, vi(ALPH));
        vvi disk2(d, vi(ALPH));
        rep(i, 0, d){
            string str; cin >> str;
            rep(j, 0, ALPH) disk[i][str[j] - 'A'] = j;
            rep(j, 0, ALPH) disk2[i][j] = str[j] - 'A';
        }
        rep(i, 0, d) cin >> lazyrotate[i];
        vi reflector(ALPH);
        string str; cin >> str;
        rep(i, 0, ALPH){
            reflector[i] = str[i] - 'A';
        }
        int q; cin >> q;
        rep(i, 0, q){
            cin >> str;
            rep(j, 0, sz(str)){
                lazyrotate[0]++;
                rep(k, 0, d){
                    if(lazyrotate[k] && lazyrotate[k] % ALPH == 0){
                        lazyrotate[k] = 0;
                        if(k + 1 < d) lazyrotate[k + 1]++;
                    }
                    else break;
                }
                int message = str[j] - 'A';
                message = patch[message];
                rep(k, 0, d){
                    message = (message + lazyrotate[k]) % ALPH;
                    message = disk[k][message];
                    message -= lazyrotate[k];
                    message = (message % ALPH + ALPH) % ALPH;
                }
                message = reflector[message];
                for(int k = d - 1; k >= 0; k--){
                    message = (message + lazyrotate[k]) % ALPH;
                    message = disk2[k][message];
                    message -= lazyrotate[k];
                    message = (message % ALPH + ALPH) % ALPH;
                }
                message = patch[message];
                cout << char('A' + message);
            }
            cout << "\n";
        }
    }
}
