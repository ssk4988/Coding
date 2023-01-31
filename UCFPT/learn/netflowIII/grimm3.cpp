#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
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

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow, cost;
	vi seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				for (int to : ed[i]) if (cap[i][to])
					if ((v = pi[i] + cost[i][to]) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll l, r;
    while (true)
    {
        cin >> l >> r;
        if (l == 0 && r == 0)
            break;
        set<ll> fset;
        vector<set<ll>> factors;
        vector<int> factorsLeft;
        map<ll, int> fm, m;
        map<int, ll> fmrev;
        int cnt = 0;
        for (ll i = l; i <= r; i++)
        {
            ll i1 = i;
            m[i] = cnt++;
            factors.pb({});
            factorsLeft.pb(0);
            for (ll k = 2; k * k <= i; k++)
            {
                if (i1 % k == 0)
                {
                    factors.back().insert(k);
                    fset.insert(k);
                    while (i1 % k == 0)
                        i1 /= k;
                }
            }
            if (i1 > 1)
            {
                factors.back().insert(i1);
                fset.insert(i1);
            }
            factorsLeft[factorsLeft.size()] = factors.back().size();
            reverse(all(factors.back()));
        }
        int firstF = cnt;
        for (ll k : fset)
        {
            fm[k] = cnt++;
            fmrev[fm[k]] = k;
        }
        int totalFactors = fset.size();
        vvi edges;
        int source = cnt++, sink = cnt++;
        rep(i, firstF, source){
            edges.pb({i, sink, 1});
        }
        rep(i, 0, factors.size())
        {
            for (int j : factors[i])
            {
                edges.pb({i, fm[j], 1});
            }
            edges.pb({source, i, 1});
            // edges.pb({i, sink, 1});
        }
        vector<bool> assn(firstF, false);
        map<ll, bool> fassn;
        int left = firstF;
        vi matching(firstF);
        int lf = 0, rf = 0; // rf excluded
        while(lf < firstF && rf < firstF){
            int bitsLeft = 55;
            while(rf < firstF && bitsLeft >= factorsLeft[rf]){
                bitsLeft -= factorsLeft[rf];
                rf++;
            }
            MCMF g(cnt);
            bitsLeft = 56;
            for(int i = lf; i < firstF; i++){
                g.addEdge(source, i, 1, 0);
                for(auto it = factors[lf].rbegin(); it != factors[lf].rend(); it = next(it)){
                    g.addEdge(i, fm[*it], 1, i < rf ? 1LL << (bitsLeft--) : 1);
                }
            }
            // for(int i = )
            // update factorsleft
            lf = rf;
        }
        rep(i, 0, firstF){
            MCMF g(cnt);
            rep(j, i, firstF){
                int numFactor = 0;
                g.addEdge(source, j, 1, 0);
                rep(k, 0, factors[j].size()){
                    if(fassn[factors[j][k]]) continue;
                    g.addEdge(j, fm[factors[j][k]], 1, i == j ? (1LL << (numFactor + 1)) : 1);
                    numFactor++;
                }
            }
            for(ll k : fset){
                g.addEdge(fm[k], sink, 1, 0);
            }
            pair<ll, ll> out = g.maxflow(source, sink);
            rep(j, 0, cnt){
                if(g.flow[i][j] > 0){
                    ll k = fmrev[j];
                    fassn[k] = true;
                    assn[i] = true;
                    matching[i] = k;
                    break;
                }
            }
        }


        // rep(i, 0, factors.size())
        // {
        //     int v = m[l + i];
        //     rep(j, 0, factors[i].size())
        //     {
        //         if (assigned[fm[factors[i][j]]])
        //             continue;
        //         int k = fm[factors[i][j]];
        //         Dinic d(cnt);
        //         for (auto &q : edges)
        //         {
        //             if (assigned[q[0]] || assigned[q[1]])
        //                 continue;
        //             if (q[0] == k || q[1] == k || q[0] == v || q[1] == v)
        //                 continue;
        //             d.addEdge(q[0], q[1], q[2]);
        //         }
        //         ll mf = d.calc(source, sink);
        //         assert(mf <= left - 1);
        //         if (mf == left - 1)
        //         {
        //             assigned[k] = true;
        //             matching[v] = factors[i][j];
        //             break;
        //         }
        //     }
        //     assigned[v] = true;
        //     left--;
        // }
        rep(i, 0, matching.size())
        {
            cout << matching[i];
            if (i + 1 < matching.size())
            {
                cout << " ";
            }
            else
            {
                cout << nL;
            }
        }
    }

    return 0;
}
