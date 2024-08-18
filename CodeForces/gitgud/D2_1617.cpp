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
        vi perm(n);
        iota(all(perm), 0);
        // shuffle
        // shuffle(all(perm));
        int numqueries = 0;
        auto query = [&](int a, int b, int c) -> int {
            numqueries++;
            assert(numqueries <= n + 6);
            cout << "? " << (a+1) << " " << (b+1) << " " << (c+1) << endl;
            int res; cin >> res;
            return res;
        };
        vi cci, iic;
        int iidx, cidx;
        vi queryres(n);
        for(int i = 0; i < n; i += 3){
            int res = query(i, i+1, i+2);
            queryres[i] = res;
            if(res){
                cci = {i, i+1, i+2};
                cidx = i;
            }
            else{
                iic = {i, i+1, i+2};
                iidx = i;
            }
        }
        vi res;
        int sum = 0;
        rep(i, 0, 3){
            if(sum == 2){
                res.pb(1);
                break;
            }
            res.pb(query(cci[0], cci[1], iic[i]));
            sum += res.back();
        }
        vi two;
        vi impostor(n);
        vi bad; // known impostors
        vi good; // known crewmates
        if(sum == 3){
            // both good
            // used 2 queries so far
            // who is two?
            good.pb(cci[0]);
            good.pb(cci[1]);
            if(query(cci[0], iic[0], iic[1])){
                // one of iic[0] and iic[1] is 10
                // therefore iic[2] = impostor
                impostor[iic[2]] = true;
                bad.pb(iic[2]);
                impostor[cci[2]] = !query(bad[0], good[0], cci[2]);
                impostor[iic[0]] = !query(bad[0], good[0], iic[0]);
                impostor[iic[1]] = !impostor[iic[0]];
            }
            else{
                bad.pb(iic[0]);
                bad.pb(iic[1]);
                impostor[iic[0]] = true;
                impostor[iic[1]] = true;
                impostor[cci[2]] = !query(good[0], bad[0], cci[2]);
                impostor[iic[2]] = !query(good[0], bad[0], iic[2]);
            }
        }
        else {
            // all bad
            // 0 and 1 is 1 crew 1 impostor
            // cci[2] is crew
            rep(i, 0, 3){
                impostor[iic[i]] = !res[i];
                if(impostor[iic[i]]) bad.pb(iic[i]);
            }
            impostor[cci[2]] = false; // known
            if(query(cci[0], cci[2], bad[0])){
                impostor[cci[1]] = true;
                good.pb(cci[0]);
            }
            else{
                impostor[cci[0]] = true;
                good.pb(cci[1]);
            }
            // SOLVE REST
            // two = {cci[0], cci[1]};
        }
        assert(sz(good));
        assert(sz(bad));
        for(int i = 0; i < n; i += 3){
            if(i == iidx || i == cidx) continue;
            if(queryres[i]){
                // cci or ccc
                int res1 = query(bad[0], i, i+1), res2 = query(bad[0], i+1, i+2);
                if(res1 && res2){
                    // none impostor
                }
                else if(res1 && !res2){
                    impostor[i+2] = true;
                }
                else if(!res1 && res2){
                    impostor[i] = true;
                }
                else{
                    impostor[i+1] = true;
                }
            }
            else{
                // iic or iii
                int res1 = query(good[0], i, i+1), res2 = query(good[0], i+1, i+2);
                if(res1 && res2){
                    impostor[i] = impostor[i+2] = true;
                }
                else if(res1 && !res2){
                    impostor[i+1] = impostor[i+2] = true;
                }
                else if(!res1 && res2){
                    impostor[i] = impostor[i+1] = true;
                }
                else if(!res1 && !res2){
                    impostor[i] = impostor[i+1] = impostor[i+2] = true;
                }
            }
        }
        bad.clear();
        rep(i, 0, n){
            if(impostor[i]) bad.pb(i);
        }
        cout << "! " << sz(bad) << " ";
        for(int i : bad){
            cout << (i+1) << " ";
        }
        cout << endl;
    }

    
    return 0;
}