from math import pi, sqrt, log
nc = int(input())

# L(t) = rt
# p(t) = r cos t + rt sin t, r sin t - rt cos t
# p'(t) = rt cos t, rt sin t

# p'^2(t) = r^2t^2
# integrand is rt


for cn in range(nc):
    h, r, w = map(int, input().split())
    def f(x):
        return x ** 2 / 2
    ans = f(w * 2 * pi)
    ans *= r
    print(f"{ans:.8f}")
