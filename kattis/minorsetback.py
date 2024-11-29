from math import log
n = int(input())
notes = []

for i in range(n):
    f = float(input())
    rel = round(log(f / 440, 2) * 12) % 12
    notes.append(rel)
seen = set(notes)

rels = [['A'], ['A#', 'Bb'], ['B'], ['C'], ['C#', 'Db'], ['D'], ['D#', 'Eb'], ['E'], ['F'], ['F#', 'Gb'], ['G'], ['G#', 'Ab']]
reldict = dict()
for i,v in enumerate(rels):
    for k in v:
        reldict[k] = i
scales = [
    ['G', 'A', 'B', 'C', 'D', 'E', 'F#'],
    ['C','D','E','F','G','A','B'],
    ['Eb','F','G','Ab','Bb','C','D'],
    ['F#','G#','A','B','C#','D','E'],
    ['G','A','Bb','C','D','Eb','F']
]

names = ['G major', 'C major', 'Eb major', 'F# minor', 'G minor']

scalerels = []
for scale in scales:
    scalerels.append(set(reldict[k] for k in scale))

keys = []
for i,scale in enumerate(scalerels):
    common =  scale.intersection(seen)
    if len(common) != len(seen): continue
    keys.append(i)
if len(keys) != 1:
    print("cannot determine key")
    exit()
key = keys[0]
print(names[key])
for note in notes:
    for lit in rels[note]:
        if lit in scales[key]:
            print(lit)
            break
