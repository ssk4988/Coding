
# input the integer from the console
T = int(input())

# as it turns out, we can precompute every angle
angles = [360 * i / 16 for i in range(16)]
directions = [
    'N',
    'NNE',
    'NE',
    'ENE',
    'E',
    'ESE',
    'SE',
    'SSE',
    'S',
    'SSW',
    'SW',
    'WSW',
    'W',
    'WNW',
    'NW',
    'NNW'
]

# create a mapping
directionToAngle = {}
for i in range(16):
    directionToAngle[directions[i]] = angles[i]

# declare a for loop in Python
for t in range(T):
    
    # get the direction
    string = input()

    # find the angle using the mapping
    angle = directionToAngle[string]

    # output
    print(f"%s is %.1f degrees" % (string, angle))

    
