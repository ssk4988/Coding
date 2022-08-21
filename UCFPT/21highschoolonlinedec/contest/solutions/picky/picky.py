import operator

# Determine which side of the line (a->b) the point c lies on using cross product
# 0 means point c lies on the line
def side(a, b, c):
    line = tuple(map(operator.sub, b, a))
    vector = tuple(map(operator.sub, c, a))
    return line[0]*vector[1]-line[1]*vector[0]

# Compute area of polygon
def area(polygon):
    result = 0
    for i in range(len(polygon)):
        a = polygon[i]
        b = polygon[(i+1)%len(polygon)]
        result += (b[0]-a[0])*(b[1]+a[1])
    return abs(result/2.0)

num_tests = int(input())

for q in range(num_tests):
    inp = input().split(" ")
    n = int(inp[0])
    m = int(inp[1])

    polygon = []
    for i in range(n):
        inp = input().split(" ")
        polygon.append((int(inp[0]), int(inp[1])))

    toppings = []
    for i in range(m):
        inp = input().split(" ")
        toppings.append((int(inp[0]), int(inp[1])))

    found_answer = False
    ans = 99999999999999
    for i in range(n):
        for j in range(i+2, n):
            num_toppings_meghan = 0
            num_toppings_natalie = 0
            good = True            

            for k in range(m):
                s = side(polygon[i], polygon[j], toppings[k])
                if s == 0:
                    good = False
                elif s < 0:
                    num_toppings_meghan = num_toppings_meghan+1
                else:
                    num_toppings_natalie = num_toppings_natalie+1

            if not good or not (num_toppings_meghan == num_toppings_natalie):
                continue

            polygon_meghan = []
            polygon_natalie = []
            for k in range(i, j+1):
                polygon_meghan.append(polygon[k])
            for k in range(j, n):
                polygon_natalie.append(polygon[k])
            for k in range(0, i+1):
                polygon_natalie.append(polygon[k])

            area_meghan = area(polygon_meghan)
            area_natalie = area(polygon_natalie)

            found_answer = True
            ans = min(ans, abs(area_meghan-area_natalie))

    if found_answer:
        print("Yes")
        print(str(ans)+"\n")
    else:
        print("No\n")
                
