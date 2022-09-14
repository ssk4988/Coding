import java.util.*;

public class tbuzzelli {
  static final double EPS = 1e-12;

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    while (in.hasNext()) {
      int n = in.nextInt();
      long minD = in.nextLong();
      Vec[] ps = new Vec[n];
      for (int i = 0; i < n; i++) {
        ps[n - i - 1] = new Vec(in.nextDouble(), in.nextDouble());
      }
      double min = 0, max = 1e9;
      for (int iter = 0; iter < 200; iter++) {
        double mid = (min + max) / 2;
        LineSeg[] segs = new LineSeg[n];
        for (int i = 0; i < n; i++) {
          Vec a = ps[i], b = ps[(i + 1) % n];
          Vec dir = b.sub(a).normalize().rot90();
          segs[i] = new LineSeg(a.add(dir.scale(mid)), b.add(dir.scale(mid)));
        }
        if (width(formPoly(segs)) >= minD) {
          min = mid;
        } else {
          max = mid;
        }
      }
      System.out.printf("%.9f\n", min);
    }
  }

  static double width(ArrayList<Vec> hull) {
    if (hull == null) return 0;
    int n = hull.size();
    double max = 0;
    int j = 0;
    for (int i = 0; i < hull.size(); i++) {
      Vec a = hull.get(i);
      Vec b = hull.get(j % n);
      while (hull.get((j + 1) % n).sub(a).mag() > b.sub(a).mag()) {
        b = hull.get((++j) % n);
      }
      max = Math.max(max, b.sub(a).mag());
    }
    return max;
  }

  static ArrayList<Vec> formPoly(LineSeg[] segs) {
    Border[] sides = new Border[segs.length];
    for (int i = 0; i < segs.length; i++)
      sides[i] =
          new Border(
              segs[i].a, segs[i].b.sub(segs[i].a).normalize(), -Double.MAX_VALUE, Double.MAX_VALUE);
    ArrayDeque<Border> q = new ArrayDeque<>();
    for (Border s : sides) {
      if (q.isEmpty()) {
        q.addLast(s);
        continue;
      }
      double left = walkQueue(q, s, true);
      if (Double.isNaN(left)) return null;
      double right = Double.MAX_VALUE;
      if (s.v.cross(q.peekFirst().v) > 0 && Double.isNaN(right = walkQueue(q, s, false)))
        return null;
      if (right > left + EPS) {
        s.l = left;
        s.r = right;
        q.addLast(s);
      }
    }
    ArrayList<Vec> res = new ArrayList<>();
    for (Border s : q) res.add(s.s.add(s.v.scale(s.l)));
    return res;
  }

  static double walkQueue(ArrayDeque<Border> q, Border s, boolean isLeft) {
    while (true) {
      if (q.isEmpty()) return Double.NaN;
      Border t = isLeft ? q.peekLast() : q.peekFirst();
      if (isLeft && t.v.cross(s.v) <= 0 || !isLeft && s.v.cross(t.v) <= 0) return Double.NaN;
      double a = -s.v.y, b = s.v.x, c = -(a * s.s.x + b * s.s.y);
      double mx = -(a * t.s.x + b * t.s.y + c) / (a * t.v.x + b * t.v.y);
      if (isLeft) t.r = Math.min(t.r, mx);
      else t.l = Math.max(t.l, mx);
      if (t.r <= t.l + EPS) {
        if (isLeft) q.pollLast();
        else q.pollFirst();
        continue;
      }
      a = -t.v.y;
      b = t.v.x;
      c = -(a * t.s.x + b * t.s.y);
      return -(a * s.s.x + b * s.s.y + c) / (a * s.v.x + b * s.v.y);
    }
  }

  static class Border {
    Vec s, v;
    double l, r;

    public Border(Vec ss, Vec vv, double ll, double rr) {
      s = ss;
      v = vv;
      l = ll;
      r = rr;
    }
  }

  static class LineSeg {
    Vec a, b;

    LineSeg(Vec aa, Vec bb) {
      a = aa;
      b = bb;
    }
  }

  static class Vec implements Comparable<Vec> {
    double x, y;

    Vec(double xx, double yy) {
      x = xx;
      y = yy;
    }

    Vec add(Vec v) {
      return new Vec(x + v.x, y + v.y);
    }

    Vec sub(Vec v) {
      return new Vec(x - v.x, y - v.y);
    }

    Vec scale(double s) {
      return new Vec(x * s, y * s);
    }

    Vec normalize() {
      return scale(1 / mag());
    }

    Vec rot90() {
      return new Vec(-y, x);
    }

    double dot(Vec v) {
      return x * v.x + y * v.y;
    }

    double cross(Vec v) {
      return x * v.y - y * v.x;
    }

    double mag2() {
      return dot(this);
    }

    double mag() {
      return Math.sqrt(mag2());
    }

    public boolean equals(Object o) {
      if (!(o instanceof Vec)) {
        return false;
      }
      return x == ((Vec) o).x && y == ((Vec) o).y;
    }

    public int compareTo(Vec v) {
      if (y == v.y) {
        return Double.compare(x, v.x);
      }
      return Double.compare(y, v.y);
    }

    public String toString() {
      return String.format("(%.3f, %.3f)", x, y);
    }
  }
}
