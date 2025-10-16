# by = [[] for _ in range(10)]
# for i in range(1, 10 ** 6):
#     ans = i.bit_length()-1
#     res = 0
#     x = i
#     while x > 1:
#         x //= 2
#         res += 1
#         if x > 1: x += 1
#     by[res-ans].append(i)
# for i in range(len(by)):
#     print(i, len(by[i]))
# print(by[0])
# x = 8
# print(x.bit_length()-1)
