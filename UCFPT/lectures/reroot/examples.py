# (subtree size, sum of distances to current root)
def combine(a, b):
    return (a.size + b.size, a.dist + b.dist + b.size)

def decombine(a, b):
    return (a.size - b.size, a.dist - b.dist - b.size)

# (subtree size, hash)
def combine(a, b):
    return (a.size + b.size, a.hash * B ** b.size + b.hash) # under mod

def decombine(a, b):
    return (a.size - b.size, (a.hash - b.hash) * B ** -b.size) # under mod


