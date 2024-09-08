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

const ld ANG_EPS = 1e-8;
const ld SIDE_EPS = 1e-5;
const ld pi = acosl(-1);

void add(vi &res, vi &cands, int b) {
    for(int cand : cands) {
        if((cand & (1 << b)) == 0) res.pb(cand | (1 << b));
    }
}

ld ang1(ld a, ld b, ld c)
{
    return acosl((b * b + c * c - a * a) / (2 * b * c));
}

inline bool sideeq(ld s1, ld s2)
{
    return abs(s1 - s2) <= SIDE_EPS;
}

inline bool angeq(ld a1, ld a2)
{
    return abs(a1 - a2) <= ANG_EPS;
}

inline bool sidelt(ld s1, ld s2)
{
    return s1 + SIDE_EPS < s2;
}

inline bool anglt(ld a1, ld a2)
{
    return a1 + ANG_EPS < a2;
}

struct Tri
{
    array<ld, 3> angles, sides;
    // triangle goes like ang[0], side[0], ang[1], side[1], ang[2], side[2]
    Tri(ld a, ld b, ld c)
    {
        sides = {a, b, c};
        angles = {ang1(b, c, a), ang1(c, a, b), ang1(a, b, c)};
    }
    Tri rot()
    {
        return Tri(sides[1], sides[2], sides[0]);
    }
    Tri rev()
    {
        return Tri(sides[2], sides[1], sides[0]);
    }
    vector<Tri> orients()
    {
        vector<Tri> res;
        Tri t(*this);
        rep(r, 0, 2)
        {
            rep(i, 0, 3)
            {
                res.pb(t);
                t = t.rot();
            }
            t = t.rev();
        }
        return res;
    }
    bool operator==(Tri o)
    {
        for (auto t : orients())
        {
            bool works = true;
            rep(j, 0, 3)
            {
                if (!sideeq(t.sides[j], o.sides[j]) || !angeq(t.angles[j], o.angles[j]))
                    works = false;
            }
            if (works)
                return true;
        }
        return false;
    }
    ld area()
    {
        return 0.5 * sides[0] * sinl(angles[1]) * sides[1];
    }
};

Tri sas(ld s1, ld a1, ld s2)
{
    return Tri(s1, s2, sqrtl(s1 * s1 + s2 * s2 - 2 * s1 * s2 * cosl(a1)));
}

template <int C>
struct Shape
{
    array<ld, C> angles, sides;
    // quad goes like ang[0], side[0], ang[1], side[1], ang[2], side[2], ang[3], side[3]
    Shape(array<ld, C> ang, array<ld, C> sid) : angles(ang), sides(sid)
    {
    }
    Shape<C> rot()
    {
        auto a1(angles), s1(sides);
        rotate(a1.begin(), a1.begin() + 1, a1.end());
        rotate(s1.begin(), s1.begin() + 1, s1.end());
        return Shape<C>(a1, s1);
    }
    Shape<C> rev()
    {
        auto a1(angles), s1(sides);
        rotate(a1.begin(), a1.begin() + 1, a1.end());
        reverse(all(a1));
        reverse(all(s1));
        return Shape<C>(a1, s1);
    }
    vector<Shape<C>> orients()
    {
        vector<Shape<C>> res;
        Shape<C> t(*this);
        rep(r, 0, 2)
        {
            rep(i, 0, C)
            {
                res.pb(t);
                t = t.rot();
            }
            t = t.rev();
        }
        return res;
    }
    bool operator==(Shape<C> o)
    {
        for (auto t : orients())
        {
            bool works = true;
            rep(j, 0, C)
            {
                if (!sideeq(t.sides[j], o.sides[j]) || !angeq(t.angles[j], o.angles[j]))
                    works = false;
            }
            if (works)
                return true;
        }
        return false;
    }
};
using Quad = Shape<4>;
using Quint = Shape<5>;

array<Tri, 4> tris{Tri{1, 1, 1}, Tri{1, 1, 1}, Tri{1, 1, 1}, Tri{1, 1, 1}};

// vi tri1(Tri t)
// {
//     vi res;
//     rep(i, 0, 4)
//     {
//         if (tris[i] == t)
//             res.pb(1 << i);
//     }
//     return res;
// }
vi tri2(Tri x)
{
    // bottom side belongs to one
    // no need to reverse since only 2 in this case
    vi res;
    for (Tri t : x.orients())
    {
        rep(bot, 0, 4)
        {
            for (auto b : tris[bot].orients())
            {
                if (sideeq(t.sides[0], b.sides[0]) && angeq(t.angles[1], b.angles[1]) && sidelt(b.sides[1], t.sides[1]))
                {
                    Tri other(t.sides[2], b.sides[2], t.sides[1] - b.sides[1]);
                    rep(top, 0, 4)
                    {
                        if (bot == top)
                            continue;
                        if (other == tris[top])
                            res.pb((1 << bot) | (1 << top));
                    }
                }
            }
        }
    }
    return res;
}

vi quad2(Quad q)
{
    vi res;
    rep(_, 0, 2)
    {
        if (anglt(q.angles[1], pi))
        {
            Tri b = sas(q.sides[0], q.angles[1], q.sides[1]);
            Tri t = sas(q.sides[2], q.angles[3], q.sides[3]);
            rep(bot, 0, 4)
            {
                if (!(b == tris[bot]))
                    continue;
                rep(top, 0, 4)
                {
                    if (bot == top || !(t == tris[top]))
                        continue;
                    res.pb((1 << top) | (1 << bot));
                }
            }
        }
        q = q.rot();
    }
    return res;
}

vi tri3(Tri x)
{
    vi res;
    // 3internal in middle
    auto ts = x.orients();
    for (Tri t : ts)
    {
        rep(bot, 0, 4)
        {
            for (Tri b : tris[bot].orients())
            {
                if (sideeq(b.sides[0], t.sides[0]) && anglt(b.angles[0], t.angles[0]) && anglt(b.angles[1], t.angles[1]))
                {
                    Quad q({t.angles[0] - b.angles[0], 2 * pi - b.angles[2], t.angles[1] - b.angles[1], t.angles[2]},
                           {b.sides[2], b.sides[1], t.sides[1], t.sides[2]});
                    auto qres = quad2(q);
                    add(res, qres, bot);
                }
            }
        }
    }

    // split into 2 tri
    for (Tri t : ts)
    {
        rep(bot, 0, 4)
        {
            for (auto b : tris[bot].orients())
            {
                if (sideeq(t.sides[0], b.sides[0]) && angeq(t.angles[1], b.angles[1]) && sidelt(b.sides[1], t.sides[1]))
                {
                    Tri other(t.sides[2], b.sides[2], t.sides[1] - b.sides[1]);
                    auto ores = tri2(other);
                    add(res, ores, bot);
                }
            }
        }
    }

    return res;
}

vi quad3(Quad x)
{
    // assume quad is convex (not possible to have concave quad with 3)
    vi res;
    for (Quad q : x.orients())
    {
        rep(bot, 0, 4)
        {
            for (Tri t : tris[bot].orients())
            {
                // tri 1 + quad 2
                if (sideeq(t.sides[0], q.sides[0]) && anglt(t.angles[0], q.angles[0]) && angeq(t.angles[1], q.angles[1]) && sidelt(t.sides[1], q.sides[1]))
                {
                    Quad o({q.angles[0] - t.angles[0], pi - t.angles[2], q.angles[2], q.angles[3]}, {t.sides[2], q.sides[1] - t.sides[1], q.sides[2], q.sides[3]});
                    auto ores = quad2(o);
                    add(res, ores, bot);
                }
                // tri 1 + tri 2
                if (sideeq(t.sides[0], q.sides[0]) && anglt(t.angles[0], q.angles[0]) && angeq(t.angles[1], q.angles[1]) && sideeq(t.sides[1], q.sides[1]))
                {
                    Tri o(t.sides[2], q.sides[2], q.sides[3]);
                    auto ores = tri2(o);
                    add(res, ores, bot);
                }
            }
        }
    }
    return res;
}

vi quint3(Quint q)
{
    // assume concave is angle[1]
    // skip regular diags since part of other case with half square
    vi res;
    rep(_, 0, 2)
    {
        rep(bot, 0, 4)
        {
            for (Tri t : tris[bot].orients())
            {
                if (sideeq(q.sides[1], t.sides[0]) && angeq(q.angles[2], t.angles[1]) && sideeq(q.sides[2], t.sides[1]) && anglt(t.angles[2], q.angles[3]))
                {
                    // tri 1 quad 2
                    if (!angeq(q.angles[1] - t.angles[0], pi))
                    {
                        Quad o({q.angles[1] - t.angles[0], q.angles[3] - t.angles[2], q.angles[4], q.angles[0]},
                               {t.sides[2], q.sides[3], q.sides[4], q.sides[0]});
                        auto ores = quad2(o);
                        add(res, ores, bot);
                    }
                    else
                    {
                        // tri 1 tri 2
                        Tri o(q.sides[0] + t.sides[2], q.sides[3], q.sides[4]);
                        auto ores = tri2(o);
                        add(res, ores, bot);
                    }
                }
            }
        }

        // reverse and rotate so concave is angle[1]
        q = q.rev();
        while (!anglt(pi, q.angles[1]))
            q = q.rot();
    }
    return res;
}

vi quad4(Quad q)
{
    // square
    vi res;

    // make quad3
    rep(bot, 0, 4)
    {
        for (Tri t : tris[bot].orients())
        {
            // tri 1 + quad 3
            if (sideeq(t.sides[0], q.sides[0]) && anglt(t.angles[0], q.angles[0]) && angeq(t.angles[1], q.angles[1]) && sidelt(t.sides[1], q.sides[1]))
            {
                Quad o({q.angles[0] - t.angles[0], pi - t.angles[2], q.angles[2], q.angles[3]}, {t.sides[2], q.sides[1] - t.sides[1], q.sides[2], q.sides[3]});
                auto ores = quad3(o);
                add(res, ores, bot);
            }
        }
    }

    // quint??? :skull:
    rep(bot, 0, 4)
    {
        for (Tri t : tris[bot].orients())
        {
            if (sideeq(q.sides[0], t.sides[0]) && anglt(t.angles[0], q.angles[0]) && anglt(t.angles[1], q.angles[1]))
            {
                Quint o({pi / 2 - t.angles[0], 2 * pi - t.angles[2], pi / 2 - t.angles[1], q.angles[2], q.angles[3]},
                        {t.sides[2], t.sides[1], q.sides[1], q.sides[2], q.sides[3]});
                auto ores = quint3(o);
                add(res, ores, bot);
            }
        }
    }

    // tri 3???
    Tri half(q.sides[0], q.sides[0], q.sides[0] * sqrtl(2));
    auto ores = tri3(half);
    rep(bot, 0, 4)
    {
        if (tris[bot] == half)
        {
            for (int cand : ores)
            {
                if ((cand & (1 << bot)) == 0)
                    res.pb(cand | (1 << bot));
            }
        }
    }

    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        ld area = 0;
        rep(i, 0, 4)
        {
            ld a, b, c;
            cin >> a >> b >> c;
            a = sqrtl(a), b = sqrtl(b), c = sqrtl(c);
            tris[i] = Tri(a, b, c);
            area += tris[i].area();
        }
        ld sidelen = sqrtl(area);
        Quad sq({pi / 2, pi / 2, pi / 2, pi / 2}, {sidelen, sidelen, sidelen, sidelen});
        auto res = quad4(sq);
        cout << min(sz(res), 1) << "\n";
    }

    return 0;
}
