#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int F = 100;
using fbs = bitset<F>;
const int MAXN = 1000;
using nbs = bitset<MAXN>;

random_device rd;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n, m, l, d, e; 

vi lens, imp;
vector<fbs> fact_mem;
// fact_mem - list of memories per fact
fbs dep_adj[F], dep[F], mutex_base[F];
// dep - all transitive dependencies

double score(fbs &crit, nbs &cand) {
    int base_score = 0;
    int len = 0;
    fbs violate, selected, selected_dep;
    rep(i, 0, n) {
        if(!cand[i]) continue;
        base_score += imp[i];
        len += lens[i];
        selected |= fact_mem[i];
    }
    if(len > l) return 0;
    double score = base_score;
    score *= 1 - pow(double(len) / l, 3);
    int critcnt = (crit & selected).count();
    score *= pow(double(critcnt) / sz(crit), 1.5);
    // int vj = 0;
    rep(i, 0, F) {
        if(!selected[i]) continue;
        // vj += (mutex_base[i] & selected).count();
        violate |= mutex_base[i] & selected;
        selected_dep |= dep[i];
    }
    int vj = violate.count();
    int mj = selected.count();
    int tj = selected_dep.count();
    score *= 1 - double(vj) / mj;
    score *= double(mj) / tj;
    return score;
}

bool accept(double E,double E_next,double T){
    // higher is better so un-negate
    double prob =  exp((E_next-E)/T);
    // double prob =  exp(-(E_next-E)/T);
    if(prob > 1) return true;
    else{
        bernoulli_distribution bd(prob); 
        return bd(rng);
    }
}

uniform_int_distribution<int> boolgen(0, 1);
uniform_int_distribution<int> ngen(0, 1);

vi modify(vi cur) {
    vi nxt(cur);
    if(sz(cur) != n) {
        // add element
        while(true) {
            int a = ngen(rng);
            auto it = find(all(cur), a);
            if(it == end(cur)) {
                nxt.push_back(a);
                break;
            }
        }
    }
    if(boolgen(rng)) {
        // remove random element of nxt
        int i = uniform_int_distribution<int>(0, sz(nxt)-1)(rng);
        nxt.erase(begin(nxt) + i);
    }
    return nxt;
}

pair<double, vi> simAnneal(vi &crit) {
    vi cur;
    while(sz(cur) == 0) cur = modify(cur);
    vi best = cur;
    double T = 1000; // Initial temperature
    double u = 0.999; // decay rate
    double cur_score = score(crit, cur);
    double best_score = score(crit, best);
    while(T > 1) {
        vi nxt = modify(cur);
        double nxt_score = score(crit, nxt);
        if(accept(cur_score, nxt_score, T)) {
            cur = nxt;
            if(nxt_score > best_score) {
                best_score = nxt_score;
                best = nxt;
            }
            cur_score = nxt_score;
        }
        T *= u;
    }
    return {best_score, best};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n >> m >> l >> d >> e;
    ngen = uniform_int_distribution<int>(0, n-1);
    lens.resize(n), imp.resize(n);
    fact_mem.resize(n); 
    rep(i, 0, n) {
        cin >> lens[i] >> imp[i];
        int k; cin >> k;
        rep(j, 0, k) {
            int u; cin >> u; u--;
            fact_mem[i][u] = 1;
        }
    }
    rep(i, 0, d) {
        int u, v; cin >> u >> v;
        u--, v--;
        dep_adj[u][v] = 1;
    }
    rep(i, 0, e) {
        int u, v; cin >> u >> v;
        u--, v--;
        mutex_base[u][v] = mutex_base[v][u] = 1;
    }
    auto dfs = [&](int u, int s, auto &&dfs) -> void {
        if(dep[s][u]) return;
        dep[s][u] = 1;
        rep(v, 0, F) if(dep_adj[u][v]) dfs(v, s, dfs);
    };
    rep(i, 0, F) dfs(i, i, dfs);
    double total_score = 0;
    rep(qid, 0, m) {
        int k; cin >> k;
        fbs crit;
        rep(i, 0, k) {
            int j; cin >> j; j--;
            crit[j] = 1;
        }
        // const int iter = 5000;
        // pair<double, vi> best = {-1, vi{}};
        // rep(_, 0, iter) {

        //     shuffle(all(crit), rng);
        //     int cur_len = 0;
        //     vi cand;
        //     for(int c : crit) {
        //         if(cur_len + lens[c] <= l) {
        //             cand.push_back(c);
        //             cur_len += lens[c];
        //         }
        //     }
        //     double sc = score(crit, cand);
        //     best = max(best, {sc, cand});
        // }
        // auto [sc, cand] = best;
        auto [sc, cand] = simAnneal(crit);
        cout << sz(cand) << " ";
        for(int c : cand) cout << c+1 << " ";
        cout << "\n";
        total_score += score(crit, cand);
    }
    cout << fixed << setprecision(8) << total_score << "\n";
    
    
    return 0;
}
